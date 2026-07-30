#include "headfile.h"

uint8_t motorA_dir=0;   //1为正转 0为反转
uint8_t motorB_dir=0;

int Encoder_count1 = 0;
int Encoder_count2 = 0;

void motor_init()    //初始化
{

		pwm_init(TIMG7,DL_TIMER_CC_0_INDEX,1000);	
		gpio_init(GPIOB,DL_GPIO_PIN_24,PB24,OUT);
		gpio_init(GPIOB,DL_GPIO_PIN_20,PB20,OUT);
	
		pwm_init(TIMG7,DL_TIMER_CC_1_INDEX,1000);	
		gpio_init(GPIOB,DL_GPIO_PIN_19,PB19,OUT);
		gpio_init(GPIOB,DL_GPIO_PIN_18,PB18,OUT);
}

void motorA_duty(int duty)
{
		pwm_update(TIMG7,DL_TIMER_CC_0_INDEX,duty);	
		gpio_set(GPIOB,DL_GPIO_PIN_24,motorA_dir);
		gpio_set(GPIOB,DL_GPIO_PIN_20,!motorA_dir);
}

void motorB_duty(int duty)
{
		pwm_update(TIMG7,DL_TIMER_CC_1_INDEX,duty);	
		gpio_set(GPIOB,DL_GPIO_PIN_19,motorB_dir);
		gpio_set(GPIOB,DL_GPIO_PIN_18,!motorB_dir);
}

void encoder_init()
{	
		exti_init(EXTI_PA12, FALLING, 1);
		gpio_init(GPIOA, DL_GPIO_PIN_13, PA13, IN_UP);
		exti_init(EXTI_PA15, FALLING, 1);
		gpio_init(GPIOA, DL_GPIO_PIN_16, PA16, IN_UP);
}
	
	
