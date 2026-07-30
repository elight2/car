#include "headfile.h"
#include "key.h"
/*
*

* 

* ??????????￡?

* ????
* UART0 -- tx: PA10 rx: PA11    ???printf????
* UART1 -- tx: PA8  rx: PA9
* UART2 -- tx: PA21 rx: PA22
* UART3 -- tx: PB2  rx: PB3

* PWM
* TIMG0_CH0  PA12
* TIMG0_CH1  PA13
* TIMG6_CH0  PB6
* TIMG6_CH1  PB7
* TIMG7_CH0  PA17
* TIMG7_CH1  PA18
* TIMG8_CH0  PA26
* TIMG8_CH1  PA27 
* TIMG12_CH0  PA14
* TIMG12_CH1  PB24

* ???????
* PWMA   PA17
* AIN1   PB24
* AIN2   PB20
* E1A    PA12
* E1B    PA13
* PWMB   PA18
* BIN1   PB19
* BIN2   PB18
* E2A	   PA15
* E2B    PA16
*
* OLED ????
* SCL  PA0
* SDA  PA1
*
* MPU6050 ????
* SCL  PB6
* SDA  PB7
*/
// ??main.c????????????
uint8_t set_N = 0;       // ?趨?????1-5??
int guaiwan = 0;

uint8_t current_circle = 0; // ?????????
uint8_t is_running = 0;   // ???????0????1????
uint32_t run_timer = 0;   // ???????(ms)

// ??????ж??????1ms????????
void tim_interrupt_callback() {
    if (is_running) {
        run_timer++;
        update_turn_timer(); // ???????????
        // ????????20s=20000ms
        if (run_timer >= 20000) {
            is_running = 0;
            pid_control(0, 0); // ????
        }
    }
}

// ????main???????????????...
int main(void) {
    system_init();
    delay_ms(500);
    uart_init(UART0, 9600, 0x02);
    OLED_Init();
    I2C_Init();
    motor_init();
    encoder_init();
    // ?????PID???????????????????????
    pid_init(&motorA, DELTA_PID, 0.2, 2, 0);
    pid_init(&motorB, DELTA_PID, 0.2, 2, 0);
    tim_interrupt_ms_init(TIMG0, 10, 1); // ???????????
    tim_interrupt_ms_init(TIMG6, 1, 1);  // 1ms?ж?????
    Key_Init();
    gray_init();



    OLED_ShowString(1, 1, "N:");
    OLED_ShowNum(1, 3, set_N, 1);
    OLED_ShowString(2, 1, "Circle:0");
    OLED_ShowString(3, 1, "Time:0");

    while(1) {
        // ??????????????...
        int a = Key_GetNum();

        
        if (a == 1 && is_running==0) {
            set_N++;
			

            OLED_ShowNum(1, 3, set_N, 1);

        }

        if (a == 2) {
            if (is_running==0) {
                is_running = 1;
                // 重置转弯状态
                turn_state = TURN_NONE;
                turn_timer = 0;
                OLED_ShowString(2, 1, "Circle:0");
                run_timer = 0; // 重置计时器
            } else {
                is_running = 0;
                pid_control(0, 0);
            }
        }

        if (is_running==1) {
			int mubiao = 4*set_N;
			
			// 使用优化的循迹函数
			track();
			
			// 更新时间显示
			uint16_t seconds = run_timer / 1000;
			uint16_t milliseconds = run_timer % 1000;
			OLED_ShowString(3, 1, "Time:");
			OLED_ShowNum(3, 6, seconds, 2);
			OLED_ShowString(3, 8, ".");
			OLED_ShowNum(3, 9, milliseconds/10, 2);
			
			// 检查是否完成目标圈数
			if(guaiwan >= mubiao)
			{
				pid_control(0, 0);
				is_running=3;
				while(1)
				{
					pid_control(0, 0);
				}
			}
        }

    }
}