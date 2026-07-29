/***********************************************
��˾����Ȥ�Ƽ�(��ݸ)���޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��V1.0
�޸�ʱ�䣺2023-05-25

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update��2023-05-25

All rights reserved
***********************************************/
#include "control.h"
//�ɸ���ʵ�ʽ����޸�
#define Frequency	400.0f			//ÿ1ms��ȡһ�α�������ֵ
#define Perimeter	0.144513f			//�����ܳ�(��λ:m)
#define MOTOR_GEAR_RATIO       20.0f    // ������ٱ�
#define ENCODER_RESOLUTION     13.0f    // ����������
#define ENCODER_DIVISION_RATIO 4.0f      // ��Ƶֵ

float Velocity_KP = 800,Velocity_KI = 700;	//���ת�ٿ���PID����

int Divider_flag=0;
float Voltage_Count,Voltage_All,Voltage;  	//��ѹ������ر��� 
Encoder OriginalEncoder; 					//������ԭʼ����   
Motor_parameter MotorA,MotorB;				//���ҵ����ر���
float Move_X =0,Move_Z = 0;						//Ŀ���ٶȺ�Ŀ��ת���ٶ�


//��ʱ��6-1ms��ʱ�жϴ�������
void TIM6_IRQHandler(void) {
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update); // ����жϱ�־λ
		Divider_flag++;
		if(Divider_flag%2==0)
		{
			Divider_flag=0;
			Led_Flash(100);
			Key();
			Voltage_All+=Get_battery_volt();  //��β����ۻ�
		    if(++Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//
		}
		Get_Velocity_From_Encoder();		//��ȡ�����ǰת��
		IRDM_line_inspection();				//����Ѳ��--���㵱ǰĿ���ٶ�
		if(Turn_Off())										//������Ƿ�رգ���ѹ�Ƿ���
		{				
			Get_Motor_PWM();										//ת�������������pwm
		}
		else
		{
			MotorA.Motor_Pwm  = 0,MotorB.Motor_Pwm = 0;
		}
		Set_Pwm(-MotorA.Motor_Pwm,MotorB.Motor_Pwm);				//�������
    }
}


//��ʼ����ʱ��6������1ms��ʱ�ж�
void TIM6_Init(void) {
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    // ʹ�ܶ�ʱ�� 6 ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    // ���ö�ʱ����������
    TIM_TimeBaseStructure.TIM_Period = 24; // �Զ���װ�ؼĴ�����ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 7199; // Ԥ��Ƶ����ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
    // ʹ�ܶ�ʱ�������ж�
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    // ���� NVIC �Դ��� TIM6 �ж�
#if defined (TIM6_IRQn)
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
#elif defined (TIM6_DAC_IRQn)
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
#else
	/* Fallback to IRQ number 54 if specific symbol not available */
	NVIC_InitStructure.NVIC_IRQChannel = (u8)54;
#endif
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // ������ռ���ȼ�Ϊ 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; // ���������ȼ�Ϊ 1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    // ������ʱ��
    TIM_Cmd(TIM6, ENABLE);
}
/**************************************************************************
Function: Get_Velocity_From_Encoder
Input   : none
Output  : none
�������ܣ���ȡ��������ת�����ٶ�
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
void Get_Velocity_From_Encoder(void)
{
	
	 //Retrieves the original data of the encoder
	  //��ȡ��������ԭʼ����
		float Encoder_A_pr,Encoder_B_pr; 
		OriginalEncoder.A=Read_Encoder(Encoder1);	
		OriginalEncoder.B=Read_Encoder(Encoder2);	
		Encoder_A_pr=OriginalEncoder.A; Encoder_B_pr=-OriginalEncoder.B;
		//������ԭʼ����ת��Ϊ�����ٶȣ���λm/s
		MotorA.Current_Encoder= Encoder_A_pr*Frequency*Perimeter/(ENCODER_DIVISION_RATIO*ENCODER_RESOLUTION*MOTOR_GEAR_RATIO);  
		MotorB.Current_Encoder= Encoder_B_pr*Frequency*Perimeter/(ENCODER_DIVISION_RATIO*ENCODER_RESOLUTION*MOTOR_GEAR_RATIO); 
}

/**************************************************************************
Function: Limiting function
Input   : Value
Output  : none
�������ܣ��޷�����
��ڲ�������ֵ
����  ֵ����
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
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)��������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_Left (float Encoder,float Target)
{ 	
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                					//����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   	//����ʽPI������
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   					//������һ��ƫ�� 
	 return Pwm;                         					//�������
}


int Incremental_PI_Right (float Encoder,float Target)
{ 	
	 static float Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                					//����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   	//����ʽPI������
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   					//������һ��ƫ�� 
	 return Pwm;                         					//�������
}
/**************************************************************************
Function: PWM_Limit
Input   : IN;max;min
Output  : OUT
�������ܣ�����PWM��ֵ
��ڲ���: IN���������  max���޷����ֵ  min���޷���Сֵ 
����  ֵ���޷����ֵ
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
�������ܣ�ת�������������PWM
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
void Get_Motor_PWM(void)
{
	//�������ҵ����Ӧ��PWM
	MotorA.Motor_Pwm = Incremental_PI_Left(MotorA.Current_Encoder,MotorA.Target_Encoder);	
	MotorB.Motor_Pwm = Incremental_PI_Right(MotorB.Current_Encoder,MotorB.Target_Encoder);
	//�޷�
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
�������ܣ��쳣�رյ��
��ڲ���: �� 
����  ֵ��1���쳣  0������
**************************************************************************/	 	
u8 Turn_Off(void)
{
	u8 temp = 0;
	if(Voltage>700&&EN==0)//��ѹ����7V��ʹ�ܿ��ش�
	{
		temp = 1;
	}
	return temp;			
}

