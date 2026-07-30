// 日期：2026-07-30 17:45 - 添加中间6路停车线检测功能
#include "headfile.h"
#include "key.h"
/*
*

* 

* 引脚定义：
* 八路灰度传感器：
* X1 (最左) -> PB9
* X2        -> PA21
* X3        -> PA22
* X4        -> PA23
* X5        -> PA24
* X6        -> PA25
* X7        -> PA26
* X8 (最右) -> PA27
* 
* 按键：PB3 - 按下直接开机运行
*
* UART
* UART0 -- tx: PA10 rx: PA11    用于printf输出
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

* 电机驱动
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
* OLED 显示
* SCL  PA0
* SDA  PA1
*
* MPU6050 姿态
* SCL  PB6
* SDA  PB7
*/

uint8_t is_running = 0;   // 运行状态：0=停止，1=运行中
uint32_t run_timer = 0;   // 运行计时器(ms)

// 定时器中断回调函数（1ms中断调用）
void tim_interrupt_callback() {
    if (is_running) {
        run_timer++;
    }
}

// main函数
int main(void) {
    system_init();
    delay_ms(500);
    uart_init(UART0, 9600, 0x02);
    OLED_Init();
    I2C_Init();
    motor_init();
    encoder_init();
    // 电机PID初始化
    pid_init(&motorA, DELTA_PID, 0.2, 2, 0);
    pid_init(&motorB, DELTA_PID, 0.2, 2, 0);
    tim_interrupt_ms_init(TIMG0, 10, 1); // 10ms定时器
    tim_interrupt_ms_init(TIMG6, 1, 1);  // 1ms中断，用于计时
    Key_Init();
    gray_init();

    // OLED初始显示
    OLED_ShowString(1, 1, "Press Key to");
    OLED_ShowString(2, 1, "  Start!  ");

    while(1) {
        int a = Key_GetNum();

        // 按键按下且未运行时，启动
        if (a == 1 && is_running == 0) {
            is_running = 1;
            run_timer = 0;
            set_stop_line_enable(1);  // 使能停车线检测
            
            OLED_ShowString(1, 1, "Running...  ");
            OLED_ShowString(2, 1, "Time:0.0s  ");
        }

        if (is_running == 1) {
            // 先检测停车线（中间6路X2~X7同时检测到黑线）
            if (check_stop_line()) {
                pid_control(0, 0);  // 停车
                is_running = 2;     // 进入停车状态
                OLED_ShowString(1, 1, "Stop! Line! ");
                uint32_t seconds = run_timer / 1000;
                uint32_t tenths = (run_timer % 1000) / 100;
                OLED_ShowString(2, 1, "Time:");
                OLED_ShowNum(2, 6, seconds, 2);
                OLED_ShowString(2, 8, ".");
                OLED_ShowNum(2, 9, tenths, 1);
                OLED_ShowString(2, 10, "s");
            } else {
                // 未检测到停车线，正常循迹
                track();
                
                // 更新OLED显示运行时间（每100ms更新一次）
                static uint32_t last_display_time = 0;
                if (run_timer - last_display_time >= 100) {
                    last_display_time = run_timer;
                    
                    uint32_t seconds = run_timer / 1000;
                    uint32_t tenths = (run_timer % 1000) / 100;
                    OLED_ShowString(2, 1, "Time:");
                    OLED_ShowNum(2, 6, seconds, 2);
                    OLED_ShowString(2, 8, ".");
                    OLED_ShowNum(2, 9, tenths, 1);
                    OLED_ShowString(2, 10, "s");
                }
            }
        }
    }
}
