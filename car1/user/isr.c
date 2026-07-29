#include "headfile.h"

// 外部函数声明（定义在main.c中）
extern void tim_interrupt_callback(void);

// 定时器中断

void TIMG0_IRQHandler()
{	
	if(DL_TimerG_getPendingInterrupt(TIMG0) == DL_TIMER_IIDX_LOAD)
	{
		// 10ms定时器 - 可用于PID速度控制
		// pid_speed_control();  // 如果启用速度PID，取消注释
	}
}

void TIMG6_IRQHandler()
{
	if(DL_TimerG_getPendingInterrupt(TIMG6) == DL_TIMER_IIDX_LOAD)
	{
		// 1ms定时器 - 系统计时
		tim_interrupt_callback();
	}
}

void TIMG7_IRQHandler()
{
	if(DL_TimerG_getPendingInterrupt(TIMG7) == DL_TIMER_IIDX_LOAD)
	{
		// 此处编写中断函数
	}
}

void TIMG8_IRQHandler()
{
	if(DL_TimerG_getPendingInterrupt(TIMG8) == DL_TIMER_IIDX_LOAD)
	{
		// 此处编写中断函数
	}
}

void TIMG12_IRQHandler()
{
	if(DL_TimerG_getPendingInterrupt(TIMG12) == DL_TIMER_IIDX_LOAD)
	{
		// 此处编写中断函数
	}
}


// 串口中断
void UART0_IRQHandler(void)
{
	if(DL_UART_getPendingInterrupt(UART0) == DL_UART_IIDX_RX)
	{
		// 此处编写中断函数
	}
 
}


void UART1_IRQHandler(void)
{
	if(DL_UART_getPendingInterrupt(UART1) == DL_UART_IIDX_RX)
	{
		// JY61/JY901陀螺仪数据接收
		imu_uart_callback();
	}
}


void UART2_IRQHandler(void)
{
	if(DL_UART_getPendingInterrupt(UART2) == DL_UART_IIDX_RX)
	{
		// 此处编写中断函数
	}
}


void UART3_IRQHandler(void)
{
	if(DL_UART_getPendingInterrupt(UART3) == DL_UART_IIDX_RX)
	{
		// 此处编写中断函数
	}
}


// 外部中断
void GROUP1_IRQHandler(void)//Group1的中断服务函数
{
		if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_12) // PA12外部中断 - 编码器1 A相
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_13))
				Encoder_count1 --;
			else
				Encoder_count1 ++;
			
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_12; // 清除中断标志位
		}	
		else if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_15) // PA15外部中断 - 编码器2 A相
		{
			if(gpio_get(GPIOA, DL_GPIO_PIN_16))
				Encoder_count2 --;
			else
				Encoder_count2 ++;
			
			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_15; // 清除中断标志位
		}
		
// 如果还需要其他外部中断引脚 可以按照下面的模板自行添加
//		if(GPIOA->CPU_INT.MIS & DL_GPIO_PIN_0) // PA0外部中断
//		{
//        // 此处编写中断执行函数
		
//			GPIOA->CPU_INT.ICLR |= DL_GPIO_PIN_0; // 清除中断标志位
//		}

}
