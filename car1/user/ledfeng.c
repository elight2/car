#include "headfile.h"

void ledfeng(void)
{
	
		gpio_set(GPIOB, DL_GPIO_PIN_8, 0);		//将PB08引脚设置为低电平，蜂鸣器鸣叫
		delay_ms(100);							//延时100ms
		gpio_set(GPIOB, DL_GPIO_PIN_8, 1);		//将PB12引脚设置为高电平，蜂鸣器停止
		delay_ms(100);							//延时100ms
	    gpio_set(GPIOB, DL_GPIO_PIN_8, 0);		//将PB12引脚设置为低电平，蜂鸣器鸣叫
		delay_ms(100);							//延时100ms
		gpio_set(GPIOB, DL_GPIO_PIN_8, 1);		//将PB12引脚设置为高电平，蜂鸣器停止
		delay_ms(700);			//延时700ms
				/*设置PA0引脚的高低电平，实现LED闪烁，下面展示3种方法*/
		
		/*方法1：GPIO_ResetBits设置低电平，GPIO_SetBits设置高电平*/
		gpio_set(GPIOB, DL_GPIO_PIN_9, 0);					//将PA0引脚设置为低电平
		delay_ms(500);										//延时500ms
		gpio_set(GPIOB, DL_GPIO_PIN_9, 1);						//将PA0引脚设置为高电平
		delay_ms(500);										//延时500ms
		
		
}