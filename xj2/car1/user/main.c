#include "headfile.h"
#include "key.h"

/*
 * 车载平衡滚球运动控制系统 - 循迹小车主程序
 *
 * 引脚定义:
 * UART0 -- tx: PA10 rx: PA11   (printf输出)
 * UART1 -- tx: PA8  rx: PA9    (JY61/JY901陀螺仪)
 * UART2 -- tx: PA21 rx: PA22
 * UART3 -- tx: PB2  rx: PB3
 *
 * 电机驱动:
 * PWMA   PA17  (TIMG7_CH0)
 * AIN1   PB24
 * AIN2   PB20
 * E1A    PA12  (编码器A相)
 * E1B    PA13  (编码器B相)
 * PWMB   PA18  (TIMG7_CH1)
 * BIN1   PB19
 * BIN2   PB18
 * E2A    PA15  (编码器A相)
 * E2B    PA16  (编码器B相)
 *
 * OLED显示:
 * SCL  PA0
 * SDA  PA1
 *
 * 灰度传感器:
 * D1 - PA21 (最左)
 * D2 - PA22 (左中)
 * D3 - PA23 (中间)
 * D4 - PA24 (右中)
 * D5 - PA25 (最右)
 *
 * 按键:
 * KEY1 - PB3 (启动)
 * KEY2 - PB2 (停止)
 */

// 系统状态变量
volatile uint8_t is_running = 0;      // 运行标志：0=停止，1=运行
volatile uint32_t run_timer = 0;      // 运行计时(ms)
volatile uint8_t lap_finished = 0;    // 圈完成标志

// 停车线检测去抖
static uint8_t stop_line_count = 0;

// 1ms定时器中断回调
void tim_interrupt_callback() {
    if (is_running) {
        run_timer++;
        
        // 超时保护（30秒）
        if (run_timer >= 30000) {
            is_running = 0;
            pid_control(0, 0);
        }
    }
}

// 检测停车线（A点启停线）
// 停车线特征：5个传感器同时检测到黑线（全黑）
uint8_t check_stop_line(void)
{
    uint8_t d1 = D1, d2 = D2, d3 = D3, d4 = D4, d5 = D5;
    
    // 5个传感器全部检测到黑线
    if(d1 && d2 && d3 && d4 && d5) {
        stop_line_count++;
        // 连续多次检测到全黑，确认是停车线
        if(stop_line_count >= 5) {
            stop_line_count = 0;
            return 1;
        }
    } else {
        stop_line_count = 0;
    }
    return 0;
}

// 显示运行信息
void display_run_info(void)
{
    // 第1行：时间
    OLED_ShowString(1, 1, "T:");
    OLED_ShowNum(1, 3, run_timer / 1000, 2);
    OLED_ShowChar(1, 5, '.');
    OLED_ShowNum(1, 6, (run_timer % 1000) / 10, 2);
    OLED_ShowString(1, 8, "s");
    
    // 第2行：传感器状态
    OLED_ShowString(2, 1, "S:");
    OLED_ShowNum(2, 3, D1, 1);
    OLED_ShowNum(2, 4, D2, 1);
    OLED_ShowNum(2, 5, D3, 1);
    OLED_ShowNum(2, 6, D4, 1);
    OLED_ShowNum(2, 7, D5, 1);
    
    // 第3行：循迹偏差
    OLED_ShowString(3, 1, "E:");
    OLED_ShowSignedNum(3, 3, track_error, 3);
    
    // 第4行：状态
    OLED_ShowString(4, 1, "St:");
    if(is_running) {
        OLED_ShowString(4, 4, "RUN");
    } else {
        OLED_ShowString(4, 4, "STP");
    }
}

int main(void) 
{
    // 系统初始化
    system_init();
    delay_ms(500);
    
    // 外设初始化
    uart_init(UART0, 9600, 0x02);     // 串口0（调试输出）
    OLED_Init();                       // OLED显示
    I2C_Init();                        // I2C初始化
    motor_init();                      // 电机初始化
    encoder_init();                    // 编码器初始化
    gray_init();                       // 灰度传感器初始化
    Key_Init();                        // 按键初始化
    
    // 初始化PID
    pid_init(&motorA, DELTA_PID, 0.2f, 2.0f, 0.0f);
    pid_init(&motorB, DELTA_PID, 0.2f, 2.0f, 0.0f);
    
    // 初始化定时器中断
    tim_interrupt_ms_init(TIMG0, 10, 1);  // 10ms定时器（预留）
    tim_interrupt_ms_init(TIMG6, 1, 1);   // 1ms定时器（计时）
    
    // 显示初始界面
    OLED_Clear();
    OLED_ShowString(1, 1, "Car Tracking");
    OLED_ShowString(2, 1, "KEY1:Start");
    OLED_ShowString(3, 1, "KEY2:Stop");
    OLED_ShowString(4, 1, "Ready");
    
    // 主循环
    while(1) 
    {
        int key = Key_GetNum();
        
        // KEY1: 启动
        if(key == 1 && is_running == 0) {
            // 启动
            is_running = 1;
            run_timer = 0;
            lap_finished = 0;
            stop_line_count = 0;
            track_error = 0;
            all_white_count = 0;
            all_black_count = 0;
            current_track = TRACK_STRAIGHT;
            
            OLED_Clear();
            OLED_ShowString(1, 1, "T:  0.00s");
            OLED_ShowString(2, 1, "S:00000");
            OLED_ShowString(3, 1, "E:  0");
            OLED_ShowString(4, 1, "St:RUN");
        }
        
        // KEY2: 停止
        if(key == 2 && is_running == 1) {
            // 停止
            is_running = 0;
            pid_control(0, 0);
            
            OLED_Clear();
            OLED_ShowString(1, 1, "T:");
            OLED_ShowNum(1, 3, run_timer / 1000, 2);
            OLED_ShowChar(1, 5, '.');
            OLED_ShowNum(1, 6, (run_timer % 1000) / 10, 2);
            OLED_ShowString(1, 8, "s");
            OLED_ShowString(4, 1, "St:STP");
        }
        
        // 运行状态 - 循迹控制
        if(is_running == 1) 
        {
            // 检测停车线（全黑5个传感器）
            if(check_stop_line()) {
                // 检测到停车线，停车
                pid_control(0, 0);
                is_running = 0;
                lap_finished = 1;
                
                // 显示最终时间
                OLED_Clear();
                OLED_ShowString(1, 1, "Finish!");
                OLED_ShowString(2, 1, "T:");
                OLED_ShowNum(2, 3, run_timer / 1000, 2);
                OLED_ShowChar(2, 5, '.');
                OLED_ShowNum(2, 6, (run_timer % 1000) / 10, 2);
                OLED_ShowString(2, 8, "s");
                OLED_ShowString(4, 1, "St:STP");
                
                // 蜂鸣器提示
                ledfeng();
                
                continue;
            }
            
            // PID循迹控制
            track_pid_control();
            
            // 更新显示（每50ms刷新一次，减少闪烁）
            static uint32_t display_timer = 0;
            display_timer++;
            if(display_timer >= 50) {
                display_timer = 0;
                display_run_info();
            }
        }
    }
}
