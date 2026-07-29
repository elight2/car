#include "headfile.h"


pid_t motorA;
pid_t motorB;
pid_t track_pid;  // 循迹PID

void pid_init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
	pid->pid_mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
	pid->target = 0;
	pid->now = 0;
	pid->error[0] = pid->error[1] = pid->error[2] = 0;
	pid->pout = pid->iout = pid->dout = 0;
	pid->out = 0;
	pid->integral_limit = 10000;
	pid->output_limit = 10000;
}

void pid_set_limit(pid_t *pid, float integral_limit, float output_limit)
{
	pid->integral_limit = integral_limit;
	pid->output_limit = output_limit;
}

void motor_target_set(int spe1, int spe2)
{
	if(spe1 >= 0)
	{
		motorA_dir = 1;
		motorA.target = spe1;
	}
	else
	{
		motorA_dir = 0;
		motorA.target = -spe1;
	}
	
	if(spe2 >= 0)
	{
		motorB_dir = 1;
		motorB.target = spe2;
	}
	else
	{
		motorB_dir = 0;
		motorB.target = -spe2;
	}
}


void pid_control(int a,int b)
{
	// 直接占空比控制模式（不使用速度PID）
	motorA_duty(a);
	motorB_duty(b);
}

// 速度PID控制（在定时器中断中调用）
void pid_speed_control(void)
{
	// 1.获取当前速度（编码器计数）
	if(motorA_dir){motorA.now = Encoder_count1;}else{motorA.now = -Encoder_count1;}
	if(motorB_dir){motorB.now = -Encoder_count2;}else{motorB.now = Encoder_count2;}
	Encoder_count1 = 0;
	Encoder_count2 = 0;
	
	// 2.PID计算
	pid_cal(&motorA);
	pid_cal(&motorB);
	
	// 3.输出限幅
	pidout_limit(&motorA);
	pidout_limit(&motorB);
	
	// 4.输出给电机
	motorA_duty((int)motorA.out);
	motorB_duty((int)motorB.out);
}

void pid_cal(pid_t *pid)
{
	// 计算当前偏差
  pid->error[0] = pid->target - pid->now;

	// 计算输出
	if(pid->pid_mode == DELTA_PID)  // 增量式
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->pid_mode == POSITION_PID)  // 位置式
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout += pid->i * pid->error[0];
		// 积分限幅
		if(pid->iout > pid->integral_limit) pid->iout = pid->integral_limit;
		if(pid->iout < -pid->integral_limit) pid->iout = -pid->integral_limit;
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}
	
	// 输出限幅
	if(pid->out > pid->output_limit) pid->out = pid->output_limit;
	if(pid->out < -pid->output_limit) pid->out = -pid->output_limit;
	
	// 记录前两次偏差
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
	
}

void pidout_limit(pid_t *pid)
{
	// 输出限幅
	if(pid->out>=MAX_DUTY/2)	
		pid->out=MAX_DUTY/2;
	if(pid->out<=0)	
		pid->out=0;
}
