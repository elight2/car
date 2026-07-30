// 日期：2026-07-30 17:28 - 方向取反（motorA_dir=0为正转）
#include "headfile.h"


pid_t motorA;
pid_t motorB;

void pid_init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
	pid->pid_mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
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
	// 电机正反转反了，方向取反
	// a=左轮速度，b=右轮速度
	int duty_a = a;  // motorA -> 左轮
	int duty_b = b;  // motorB -> 右轮
	
	// 正转（方向取反）
	if(duty_a > 0)
	{
		motorA_dir = 0;  // 正转
	}
	else if(duty_a < 0)
	{
		motorA_dir = 1;  // 反转
		duty_a = -duty_a;
	}
	// duty_a == 0 时保持方向不变
	
	if(duty_b > 0)
	{
		motorB_dir = 0;  // 正转
	}
	else if(duty_b < 0)
	{
		motorB_dir = 1;  // 反转
		duty_b = -duty_b;
	}
	// duty_b == 0 时保持方向不变
	
	// 限幅（MAX_DUTY=10000）
	if(duty_a > 10000) duty_a = 10000;
	if(duty_b > 10000) duty_b = 10000;
	
	motorA_duty(duty_a);
	motorB_duty(duty_b);
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
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}
	// 记录前两次偏差
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
	
}

void pidout_limit(pid_t *pid)
{
	// 输出限幅
	if(pid->out>=MAX_DUTY/5)	
		pid->out=MAX_DUTY/5;
	if(pid->out<=0)	
		pid->out=0;
}
