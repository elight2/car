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
#include "adc.h"

/**************************************************************************
Function: Initialize the ADC
Input   : none
Output  : none
�������ܣ�ACD��ʼ����ص�ѹ���
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 		
void Adc_Init(void)
{    
 	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC2	, ENABLE );	  //使能ADC2通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //配置ADC时钟分频 72M/6=12,ADC采样时间不能超过14M
	
	//配置模拟输入通道：STM32F103C8T6 上使用 PA1/PA2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	
	ADC_DeInit(ADC2);  //��λADC2,������ ADC2 ��ȫ���Ĵ�������Ϊȱʡֵ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת���������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC2, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	ADC_Cmd(ADC2, ENABLE);	//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC2);	//ʹ�ܸ�λУ׼  	 
	while(ADC_GetResetCalibrationStatus(ADC2));	//�ȴ���λУ׼����	
	ADC_StartCalibration(ADC2);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC2));	 //�ȴ�У׼����
}		



/**************************************************************************
Function: AD sampling
Input   : ch��Channel of ADC1
Output  : AD conversion result
�������ܣ�AD����
��ڲ���: ch��ADC2 ��ͨ��
����  ֵ��ADת�����
**************************************************************************/	 		
u16 Get_Adc(u8 ch)   
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC2,ADCͨ��,����ʱ��Ϊ239.5����	  			     
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);		//ʹ��ָ����ADC2������ת����������		 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC2);	//�������һ��ADC1�������ת�����
}

//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_us(1);
	}
	return temp_val/times;
} 
	
/**************************************************************************
Function: Read battery voltage
Input   : none
Output  : Battery voltage��MV��
�������ܣ���ȡ��ص�ѹ 
��ڲ���: ��
����  ֵ����ص�ѹ ��λMV
**************************************************************************/
int Get_battery_volt(void)   
{  
	int Volt;//��ص�ѹ
	Volt=Get_Adc(Battery_Ch)*3.3*11*100/4096;	//�����ѹ���������ԭ��ͼ�򵥷������Եõ�	
	return Volt;
}


/**************************************************************************
Function: Get_Voltage
Input   : none
Output  : none
�������ܣ���ȡADC��ֵ
��ڲ���: �� 
����  ֵ����
**************************************************************************/	 
//��ȡADC��ֵ
u16 Get_Adc1(u8 ch)   
{
	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1������ת����������	
	__nop();
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

