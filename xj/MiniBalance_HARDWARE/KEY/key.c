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
#include "key.h"
#include "TrackModule.h"
/**************************************************************************
Function: Key initialization
Input   : none
Output  : none
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PA�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	            //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;         //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	            //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;         //��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA 
} 
/**************************************************************************
�������ܣ�����ɨ��
��ڲ�����˫���ȴ�ʱ��
����  ֵ������״̬ 0���޶��� 1������ 2��˫�� 
**************************************************************************/
u8 click_N_Double (u8 time)
{
		static	u8 flag_key,count_key,double_key;	
		static	u16 count_single,Forever_count;
	  if(KEY==0)  Forever_count++;   //������־λδ��1
     else        Forever_count=0;
		if(0==KEY&&0==flag_key)		flag_key=1;	
	  if(0==count_key)
		{
				if(flag_key==1) 
				{
					double_key++;
					count_key=1;	
				}
				if(double_key==2) 
				{
					double_key=0;
					count_single=0;
					return 2;//˫��ִ�е�ָ��
				}
		}
		if(1==KEY)			flag_key=0,count_key=0;
		
		if(1==double_key)
		{
			count_single++;
			if(count_single>time&&Forever_count<time)
			{
			double_key=0;
			count_single=0;	
			return 1;//����ִ�е�ָ��
			}
			if(Forever_count>time)
			{
			double_key=0;
			count_single=0;	
			}
		}	
		return 0;
}
/**************************************************************************
�������ܣ��������
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������2s
**************************************************************************/
u8 Long_press(void)
{
		static int Long_Press_count=0,Long_Press_1=0;
	    if(Long_Press_1==0&&KEY==0)  Long_Press_count++;   //������־λδ��1
		else                       Long_Press_count=0; 
		if(Long_Press_count>200)		
		{
			Long_Press_1=1;	
			Long_Press_count=0;
			return 1;
		}
		 if(Long_Press_1==1)     //������־λ��1
		{
			  Long_Press_1=0;
		}
		return 0;
}
void Key(void)
{	
	u8 tmp,tmp2;
	tmp=click_N_Double(50); //��˫�����
    tmp2=Long_press();//�������
	if(tmp==1)
	{
		if(Track_Run == 0)
		{
			Track_Run_TimeMs = 0;
			Track_Finish_Flag = 0;
			Track_Run = 1;
		}
		else
		{
			Track_Run = 0;
		}
	}	
	if(tmp==2);  //˫����ȡ���
	if(tmp2==1)
	{
		Track_Run = 0;
		Track_Run_TimeMs = 0;
		Track_Finish_Flag = 0;
	}
}
