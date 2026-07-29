/***********************************************
��˾����Ȥ�Ƽ�(��ݸ)���޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��V1.0
�޸�ʱ�䣺2022-09-05

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update��2022-09-05

All rights reserved
***********************************************/
#include "encoder.h"
#include "stm32f10x_gpio.h"

/**************************************************************************
Function: Encoder_GPIO_Config
Input   : none
Output  : none
�������ܣ��������˿�����
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
void Encoder_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//������������GPIO�Ķ˿�ʱ��
	RCC_APB2PeriphClockCmd( ENCODER1_GPIO_CLK|ENCODER2_GPIO_CLK, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = ENCODER1_A_GPIO_PIN|ENCODER1_B_GPIO_PIN;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 					//��������
	GPIO_Init(ENCODER1_GPIO_PORT, &GPIO_InitStructure); 					//�����趨������ʼ��

	GPIO_InitStructure.GPIO_Pin = ENCODER2_A_GPIO_PIN|ENCODER2_B_GPIO_PIN;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 					//��������
	GPIO_Init(ENCODER2_GPIO_PORT, &GPIO_InitStructure); 					//�����趨������ʼ��

}

/**************************************************************************
Function: Encoder_NVIC_Config
Input   : none
Output  : none
�������ܣ��������ж�����
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
void Encoder_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	NVIC_InitStruct.NVIC_IRQChannel = ENCODER1_IRQ;  		//��ʱ��4�ж�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  			//ʹ��IRQͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�1 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;       	//��Ӧ���ȼ�3
	NVIC_Init(&NVIC_InitStruct);

	#if defined (TIM8_UP_IRQn)
    NVIC_InitStruct.NVIC_IRQChannel = TIM8_UP_IRQn;   	// TIM8 update IRQ
	#elif defined (TIM8_IRQn)
    NVIC_InitStruct.NVIC_IRQChannel = TIM8_IRQn;   	// TIM8 IRQ
	#else
    NVIC_InitStruct.NVIC_IRQChannel = (u8)44;   	// fallback numeric IRQ for TIM8 update
	#endif
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;  			//ʹ��IRQͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�1 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;       	//��Ӧ���ȼ�3
	NVIC_Init(&NVIC_InitStruct);
	
}
/**************************************************************************
Function: Encoder_TIM_Mode_Config
Input   : none
Output  : none
�������ܣ�������ģʽ����
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
void Encoder_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
	TIM_ICInitTypeDef TIM_ICInitStructure;  

	ENCODER1_TIM_APBxClock_FUN(ENCODER1_TIM_CLK,ENABLE);		//������1ʱ��

	ENCODER2_TIM_APBxClock_FUN(ENCODER2_TIM_CLK,ENABLE);		//������2ʱ��

	/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00; 				// Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD; 		//�趨�������Զ���װֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//ѡ��ʱ�ӷ�Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ؼ���ģʽ 
	
	TIM_TimeBaseInit(ENCODER1_TIM, &TIM_TimeBaseStructure);  	//��ʼ����ʱ��
	TIM_TimeBaseInit(ENCODER2_TIM, &TIM_TimeBaseStructure);  	//��ʼ����ʱ��

	/*--------------------������ģʽ�ӿ�����-------------------------*/
	//������1
	TIM_EncoderInterfaceConfig(ENCODER1_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3

	TIM_ICStructInit(&TIM_ICInitStructure); 					//��TIM_ICInitStruct �е�ÿһ��������ȱʡֵ����
	TIM_ICInitStructure.TIM_ICFilter = 10;  					//�����˲�������
	
	TIM_ICInit(ENCODER1_TIM, &TIM_ICInitStructure);				//���� TIM_ICInitStruct �Ĳ�����ʼ������	TIMx
	TIM_ClearFlag(ENCODER1_TIM, TIM_FLAG_Update);				//���TIM�ĸ��±�־λ
	TIM_ITConfig(ENCODER1_TIM, TIM_IT_Update, ENABLE);			//ʹ�ܶ�ʱ���ж�
	TIM_Cmd(ENCODER1_TIM, ENABLE); 								//ʹ�ܶ�ʱ��



	//������2
	TIM_EncoderInterfaceConfig(ENCODER2_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3

	TIM_ICStructInit(&TIM_ICInitStructure); 					//��TIM_ICInitStruct �е�ÿһ��������ȱʡֵ����
	TIM_ICInitStructure.TIM_ICFilter = 10;  					//�����˲�������
	
	TIM_ICInit(ENCODER2_TIM, &TIM_ICInitStructure);				//���� TIM_ICInitStruct �Ĳ�����ʼ������	TIMx
	TIM_ClearFlag(ENCODER2_TIM, TIM_FLAG_Update);				//���TIM�ĸ��±�־λ
	TIM_ITConfig(ENCODER2_TIM, TIM_IT_Update, ENABLE);			//ʹ�ܶ�ʱ���ж�
	TIM_Cmd(ENCODER2_TIM, ENABLE); 								//ʹ�ܶ�ʱ��

}

/**************************************************************************
Function: Encoder_Init
Input   : none
Output  : none
�������ܣ�����������
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 	
void Encoder_Init(void)
{
	Encoder_GPIO_Config();			//�˿�����
	Encoder_NVIC_Config();			//�ж�����
	Encoder_TIM_Mode_Config();		//ģʽ����
}

/**************************************************************************
Function: Read_Encoder
Input   : TIMX:Timer Number
Output  : Encoder data
�������ܣ���ȡ������
��ڲ���: TIMX: ���������
����  ֵ������������
**************************************************************************/	 	
int Read_Encoder(u8 TIMX)
{
	int Encoder_TIM;    
	switch(TIMX)
	{
		case 2:  Encoder_TIM= (short)TIM2 -> CNT;  TIM2 -> CNT=0; break;
		case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0; break;	
		case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0; break;	
		case 8:  Encoder_TIM= (short)TIM8 -> CNT;  TIM8 -> CNT=0; break;	
		default:  Encoder_TIM=0;
	}
	return Encoder_TIM;
}

/**************************************************************************
�������ܣ�������1�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void ENCODER1_IRQHandler(void)//�жϴ�������Ϊ�գ�����жϱ�־λ������ж�
{ 		    		  			    
	if(TIM_GetFlagStatus(ENCODER1_TIM,TIM_FLAG_Update)==SET)//����ж�
	{
	 
	} 
	TIM_ClearITPendingBit(ENCODER1_TIM,TIM_IT_Update); 	//����жϱ�־λ 	
}
/**************************************************************************
�������ܣ�������2�жϷ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void ENCODER2_IRQHandler(void)//�жϴ�������Ϊ�գ�����жϱ�־λ������ж�
{ 		    		  			    
	if(TIM_GetFlagStatus(ENCODER2_TIM,TIM_FLAG_Update)==SET)//����ж�
	{
	 
	} 
	TIM_ClearITPendingBit(ENCODER2_TIM,TIM_IT_Update); 	//����жϱ�־λ 	  
}

