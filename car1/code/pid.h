#ifndef __PID_h_
#define __PID_h_
#include "headfile.h"

enum
{
  POSITION_PID = 0,  // 位置式
  DELTA_PID,         // 增量式
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	float integral_limit;  // 积分限幅
	float output_limit;    // 输出限幅
	
	uint32_t pid_mode;

}pid_t;

void pid_cal(pid_t *pid);
void pid_control(int a,int b);
void pid_speed_control(void);
void pid_init(pid_t *pid, uint32_t mode, float p, float i, float d);
void pid_set_limit(pid_t *pid, float integral_limit, float output_limit);
void motor_target_set(int spe1, int spe2);
void pidout_limit(pid_t *pid);

extern pid_t motorA;
extern pid_t motorB;
extern pid_t track_pid;  // 循迹PID

#endif
