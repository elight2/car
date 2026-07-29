/***********************************************
公司：轮趣科技(东莞)有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：V1.0
修改时间：2023-05-25

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update：2023-05-25

All rights reserved
***********************************************/
#include "control.h"
//可根据实际进行修改
#define Frequency	400.0f			//每1ms读取一次编码器的值
#define Perimeter	0.144513f			//轮子周长(单位:m)
#define MOTOR_GEAR_RATIO       20.0f    // 电机减速比
#define ENCODER_RESOLUTION     13.0f    // 编码器线数
#define ENCODER_DIVISION_RATIO 4.0f      // 分频值

float Velocity_KP = 800,Velocity_KI = 700;	//电机转速控制PID参数

int Divider_flag=0;
float Voltage_Count,Voltage_All,Voltage;  	//电压采样相关变量 
Encoder OriginalEncoder; 					//编码器原始数据   
Motor_parameter MotorA,MotorB;				//左右电机相关变量
float Move_X =0,Move_Z = 0;						//目标速度和目标转向速度


//定时器6-1ms定时中断处理函数
void TIM6_IRQHandler(void) {
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update); // 清除中断标志位
		Divider_flag++;
		if(Divider_flag%2==0)
		{
			Divider_flag=0;
			Led_Flash(100);
			Key();
			Voltage_All+=Get_battery_volt();  //多次采样累积
		    if(++Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//
		}
		Get_Velocity_From_Encoder();		//获取电机当前转速
		IRDM_line_inspection();				//红外巡线--计算当前目标速度
		if(Turn_Off())										//检查电机是否关闭，电压是否不足
		{				
			Get_Motor_PWM();										//转换成驱动电机的pwm
		}
		else
		{
			MotorA.Motor_Pwm  = 0,MotorB.Motor_Pwm = 0;
		}
		Set_Pwm(-MotorA.Motor_Pwm,MotorB.Motor_Pwm);				//驱动电机
    }
}


//初始化定时器6，生成1ms定时中断
void TIM6_Init(void) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    // 使能定时器 6 时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    // 配置定时器基本参数
    TIM_TimeBaseStructure.TIM_Period = 24; // 自动重装载寄存器的值
    TIM_TimeBaseStructure.TIM_Prescaler = 7199; // 预分频器的值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    // 使能定时器更新中断
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    // 配置 NVIC 以处理 TIM6 中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 设置抢占优先级为 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // 设置子优先级为 1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // 启动定时器
    TIM_Cmd(TIM6, ENABLE);
}
/**************************************************************************
Function: Get_Velocity_From_Encoder
Input   : none
Output  : none
函数功能：读取编码器和转换成速度
入口参数: 无 
返回  值：无
**************************************************************************/	 	
void Get_Velocity_From_Encoder(void)
{
	
	 //Retrieves the original data of the encoder
	  //获取编码器的原始数据
		float Encoder_A_pr,Encoder_B_pr; 
		OriginalEncoder.A=Read_Encoder(Encoder1);	
		OriginalEncoder.B=Read_Encoder(Encoder2);	
		Encoder_A_pr=OriginalEncoder.A; Encoder_B_pr=-OriginalEncoder.B;
		//编码器原始数据转换为车轮速度，单位m/s
		MotorA.Current_Encoder= Encoder_A_pr*Frequency*Perimeter/(ENCODER_DIVISION_RATIO*ENCODER_RESOLUTION*MOTOR_GEAR_RATIO);  
		MotorB.Current_Encoder= Encoder_B_pr*Frequency*Perimeter/(ENCODER_DIVISION_RATIO*ENCODER_RESOLUTION*MOTOR_GEAR_RATIO); 
}

/**************************************************************************
Function: Limiting function
Input   : Value
Output  : none
函数功能：限幅函数
入口参数：幅值
返回  值：无
**************************************************************************/
float target_limit_float(float insert,float low,float high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;	
}
int target_limit_int(int insert,int low,int high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;	
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_Left (float Encoder,float Target)
{ 	
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                					//计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   	//增量式PI控制器
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   					//保存上一次偏差 
	 return Pwm;                         					//增量输出
}


int Incremental_PI_Right (float Encoder,float Target)
{ 	
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                					//计算偏差
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   	//增量式PI控制器
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   					//保存上一次偏差 
	 return Pwm;                         					//增量输出
}
/**************************************************************************
Function: PWM_Limit
Input   : IN;max;min
Output  : OUT
函数功能：限制PWM赋值
入口参数: IN：输入参数  max：限幅最大值  min：限幅最小值 
返回  值：限幅后的值
**************************************************************************/	 	
float PWM_Limit(float IN,float max,float min)
{
	float OUT = IN;
	if(OUT>max) OUT = max;
	if(OUT<min) OUT = min;
	return OUT;
}
/**************************************************************************
Function: Get_Motor_PWM
Input   : none
Output  : none
函数功能：转换成驱动电机的PWM
入口参数: 无 
返回  值：无
**************************************************************************/	 	
void Get_Motor_PWM(void)
{
	//计算左右电机对应的PWM
	MotorA.Motor_Pwm = Incremental_PI_Left(MotorA.Current_Encoder,MotorA.Target_Encoder);	
	MotorB.Motor_Pwm = Incremental_PI_Right(MotorB.Current_Encoder,MotorB.Target_Encoder);
	//限幅
	MotorA.Motor_Pwm  = PWM_Limit(MotorA.Motor_Pwm,7000,-7000);
	MotorB.Motor_Pwm  = PWM_Limit(MotorB.Motor_Pwm,7000,-7000);
}

void Set_Pwm(int motor_a,int motor_b)
{
	
	if(motor_a<0)		PWMA_IN1=7200,PWMA_IN2=7200+motor_a;
	else 	            PWMA_IN2=7200,PWMA_IN1=7200-motor_a;

	if(motor_b<0)		PWMB_IN1=7200,PWMB_IN2=7200+motor_b;
	else 	            PWMB_IN2=7200,PWMB_IN1=7200-motor_b;
}
/**************************************************************************
Function: Check whether it is abnormal
Input   : none
Output  : 1:Abnormal;0:Normal
函数功能：异常关闭电机
入口参数: 无 
返回  值：1：异常  0：正常
**************************************************************************/	 	
u8 Turn_Off(void)
{
	u8 temp = 0;
	if(Voltage>700&&EN==0)//电压高于7V且使能开关打开
	{
		temp = 1;
	}
	return temp;			
}

