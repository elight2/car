/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��V1.0
�޸�ʱ�䣺2023-03-02

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update��2023-03-02

All rights reserved
***********************************************/


#ifndef __ENCODER_H
#define	__ENCODER_H

#include "stm32f10x.h"


#define 	ENCODER_TIM_PERIOD 				(u16)(65535)  	 	//���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�
#define	 	Encoder1  						4
#define 	Encoder2  						8

//������1��ʱ��
#define  	ENCODER1_TIM                   	TIM4
#define  	ENCODER1_TIM_APBxClock_FUN    	RCC_APB1PeriphClockCmd
#define  	ENCODER1_TIM_CLK               	RCC_APB1Periph_TIM4


//������1�˿�
#define 	ENCODER1_GPIO_PORT    			GPIOB			              /* GPIO�˿� */
#define 	ENCODER1_GPIO_CLK 	   	 		RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define 	ENCODER1_A_GPIO_PIN				GPIO_Pin_7			        /* ���ӵ�A���GPIO */
#define 	ENCODER1_B_GPIO_PIN				GPIO_Pin_6			        /* ���ӵ�B���GPIO */

//�ж�
#define  	ENCODER1_IRQ                	TIM4_IRQn
#define  	ENCODER1_IRQHandler         	TIM4_IRQHandler


//������2��ʱ��
#define  	ENCODER2_TIM                   	TIM8
#define  	ENCODER2_TIM_APBxClock_FUN     	RCC_APB2PeriphClockCmd
#define  	ENCODER2_TIM_CLK               	RCC_APB2Periph_TIM8

//������2�˿�
#define	 	ENCODER2_GPIO_PORT    			GPIOC			              /* GPIO�˿� */
#define	 	ENCODER2_GPIO_CLK 	    		RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */
#define	 	ENCODER2_A_GPIO_PIN				GPIO_Pin_7			        /* ���ӵ�A���GPIO */
#define	 	ENCODER2_B_GPIO_PIN				GPIO_Pin_6			        /* ���ӵ�B���GPIO */


#if defined (TIM8_UP_IRQn)
#define   ENCODER2_IRQ                TIM8_UP_IRQn
#elif defined (TIM8_IRQn)
#define   ENCODER2_IRQ                TIM8_IRQn
#else
/* Fallback to IRQ number 44 (TIM8 Update) if symbol missing */
#define   ENCODER2_IRQ                ((u8)44)
#endif
#define  	ENCODER2_IRQHandler         	TIM8_UP_IRQHandler



void Encoder_GPIO_Config(void);
void Encoder_NVIC_Config(void);
void Encoder_TIM_Mode_Config(void);
void Encoder_Init(void);
int Read_Encoder(u8 TIMX);


#endif
