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
// ADC 通道定义：STM32F103C8T6 上改为 PA1/PA2
#define    ELE_ADC_L_CHANNEL					 ADC_Channel_4
#define    ELE_ADC_M_CHANNEL					 ADC_Channel_5
#define    ELE_ADC_R_CHANNEL					 ADC_Channel_15
#define    CCD_ADC_CHANNEL				 	 ADC_Channel_15

#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#define Battery_Ch ADC_Channel_1   // PA1
#define Angle_Ch   ADC_Channel_2   // PA2

void Adc_Init(void);
u16 Get_Adc_Average(u8 ch,u8 times);

u16 Get_Adc(u8 ch);
int Get_battery_volt(void);   
u16 Get_Adc1(u8 ch);
#endif 















