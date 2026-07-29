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
#include "led.h"
/**************************************************************************
Function: Led initialization
Input   : none
Output  : none
�������ܣ�LED�ӿڳ�ʼ��
��ڲ������� 
����  ֵ����
**************************************************************************/
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;              //PA8
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50M
  GPIO_Init(GPIOA, &GPIO_InitStructure);                //初始化GPIOA
}

/**************************************************************************
Function: Led flashing
Input   : time��Flicker frequency
Output  : none
�������ܣ�LED��˸
��ڲ�������˸Ƶ�� 
����  ֵ����
**************************************************************************/
void Led_Flash(u16 time)
{
	 static int temp;
	 if(0==time) LED=1;
	 else 	if(++temp==time)	LED=~LED,temp=0;
}
