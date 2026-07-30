// 日期：2026-07-30 17:45 - 添加中间6路停车线检测功能
#include"headfile.h"
#include <stdlib.h>

// 循迹参数 - MAX_DUTY=10000
#define STRAIGHT_SPEED 4000    // 直线速度 (40%占空比)

// 停车线检测相关
static uint8_t stop_line_enable = 0;  // 停车线检测使能
static uint8_t stop_line_detected = 0; // 是否已检测到停车线

// 设置停车线检测使能
void set_stop_line_enable(uint8_t enable) {
    stop_line_enable = enable;
    if (!enable) {
        stop_line_detected = 0; // 关闭使能时重置检测状态
    }
}

// 检测中间6路（X2~X7）是否同时检测到黑线（停车线）
// 返回值：1=检测到停车线，0=未检测到
uint8_t check_stop_line(void) {
    if (!stop_line_enable) return 0;    // 未使能，直接返回
    if (stop_line_detected) return 1;   // 已经检测过了，保持返回1
    
    uint8_t d2 = D2, d3 = D3, d4 = D4, d5 = D5, d6 = D6, d7 = D7;
    
    // 中间6路（X2~X7）全部检测到黑线（=1），判定为停车线
    if (d2 && d3 && d4 && d5 && d6 && d7) {
        stop_line_detected = 1;
        return 1;
    }
    
    return 0;
}

void gray_init()
{
    // 初始化八路灰度传感器引脚
    gpio_init(GPIOB, DL_GPIO_PIN_9, PB9, IN_UP);    // X1 - PB9  最左
    gpio_init(GPIOA, DL_GPIO_PIN_21, PA21, IN_UP);  // X2 - PA21
    gpio_init(GPIOA, DL_GPIO_PIN_22, PA22, IN_UP);  // X3 - PA22
    gpio_init(GPIOA, DL_GPIO_PIN_23, PA23, IN_UP);  // X4 - PA23
    gpio_init(GPIOA, DL_GPIO_PIN_24, PA24, IN_UP);  // X5 - PA24
    gpio_init(GPIOA, DL_GPIO_PIN_25, PA25, IN_UP);  // X6 - PA25
    gpio_init(GPIOA, DL_GPIO_PIN_26, PA26, IN_UP);  // X7 - PA26
    gpio_init(GPIOA, DL_GPIO_PIN_27, PA27, IN_UP);  // X8 - PA27  最右
}

// 循迹主逻辑
// 策略：检测到哪路偏，就向反方向转
// D1=最左，D8=最右
void track() {
    uint8_t d1 = D1, d2 = D2, d3 = D3, d4 = D4, d5 = D5, d6 = D6, d7 = D7, d8 = D8;
    
    int left_speed, right_speed;
    
    // 判断哪几路检测到黑线，计算加权位置
    // 权重：D1=-4, D2=-3, D3=-2, D4=-1, D5=1, D6=2, D7=3, D8=4
    int pos = 0;
    int cnt = 0;
    
    if (d1) { pos += -4; cnt++; }
    if (d2) { pos += -3; cnt++; }
    if (d3) { pos += -2; cnt++; }
    if (d4) { pos += -1; cnt++; }
    if (d5) { pos +=  1; cnt++; }
    if (d6) { pos +=  2; cnt++; }
    if (d7) { pos +=  3; cnt++; }
    if (d8) { pos +=  4; cnt++; }
    
    // 没有检测到黑线，直行
    if (cnt == 0) {
        pid_control(STRAIGHT_SPEED, STRAIGHT_SPEED);
        return;
    }
    
    // 计算平均位置
    int avg = pos / cnt;
    
    // 根据位置决定差速
    // avg为负=偏左，需要右转（左轮快，右轮慢）
    // avg为正=偏右，需要左转（左轮慢，右轮快）
    // 偏差越大，差速越大
    
    // 基础差速系数
    int diff = abs(avg) * 600;  // 每级偏差差速600
    
    if (avg < 0) {
        // 偏左：左轮加速，右轮减速（右转）
        left_speed = STRAIGHT_SPEED + diff;
        right_speed = STRAIGHT_SPEED - diff;
    } else if (avg > 0) {
        // 偏右：左轮减速，右轮加速（左转）
        left_speed = STRAIGHT_SPEED - diff;
        right_speed = STRAIGHT_SPEED + diff;
    } else {
        // 居中，直行
        left_speed = STRAIGHT_SPEED;
        right_speed = STRAIGHT_SPEED;
    }
    
    // 限幅
    if (left_speed < 500)  left_speed = 500;   // 最低速度500，保持转动
    if (right_speed < 500) right_speed = 500;
    if (left_speed > 10000) left_speed = 10000;
    if (right_speed > 10000) right_speed = 10000;
    
    pid_control(left_speed, right_speed);
}

// 读取单个灰度传感器值
// 返回值：0=黑线，1=白线
unsigned char digtal(unsigned char channel)
{
    char value = 0;
    switch(channel) 
    {
        case 1:  value = gpio_get(GPIOB, DL_GPIO_PIN_9) ? 1 : 0; break;
        case 2:  value = gpio_get(GPIOA, DL_GPIO_PIN_21) ? 1 : 0; break;
        case 3:  value = gpio_get(GPIOA, DL_GPIO_PIN_22) ? 1 : 0; break;
        case 4:  value = gpio_get(GPIOA, DL_GPIO_PIN_23) ? 1 : 0; break;
        case 5:  value = gpio_get(GPIOA, DL_GPIO_PIN_24) ? 1 : 0; break;
        case 6:  value = gpio_get(GPIOA, DL_GPIO_PIN_25) ? 1 : 0; break;
        case 7:  value = gpio_get(GPIOA, DL_GPIO_PIN_26) ? 1 : 0; break;
        case 8:  value = gpio_get(GPIOA, DL_GPIO_PIN_27) ? 1 : 0; break;
        default: value = 0; break;
    }
    return value; 
}
