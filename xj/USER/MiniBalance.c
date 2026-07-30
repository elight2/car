/***********************************************
公司：轮趣科技（东莞）有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：1.0
修改时间：2025-04-18

 
Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:1.0
修改时间：2025-04-18

All rights reserved
***********************************************/
#include "stm32f10x.h"
#include "sys.h" 
int main(void)
{ 
	MY_NVIC_PriorityGroupConfig(2);	//设置中断分组
	delay_init();	    	        //延时函数初始化	
	JTAG_Set(JTAG_SWD_DISABLE);     //关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //打开SWD接口 可以利用主板的SWD接口调试
	LED_Init();                     //初始化与 LED 连接的硬件接口
	KEY_Init();                     //按键初始化
	BEEP_GPIO_Config();             //蜂鸣器初始化
	MiniBalance_PWM_Init(7199,0);   //初始化PWM 10KHZ与电机硬件接口，用于驱动电机
	uart_init(115200);	            //串口1初始化
	uart3_init(9600);				//串口3初始化--蓝牙模块
	Encoder_Init();					//编码器初始化，TIM4和TIM8
	Adc_Init();                     //adc初始化
	OLED_Init();                    //OLED初始化	 	  
	TIM6_Init(); 
	TrackModule_Init();
	while(1)
	{
		APP_Show();
		oled_show();
		delay_ms(50);
	}
}

