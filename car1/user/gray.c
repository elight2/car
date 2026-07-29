#include "headfile.h"

// 全局变量定义
TurnState turn_state = TURN_NONE;
uint32_t turn_timer = 0;
int16_t track_error = 0;          // 循迹偏差（-100~100）
uint8_t all_white_count = 0;      // 全白计数（用于弯道检测）
uint8_t all_black_count = 0;      // 全黑计数（用于十字检测）
TrackType current_track = TRACK_STRAIGHT;  // 当前赛道类型

// PID循迹参数
#define TRACK_P 0.8f
#define TRACK_I 0.01f
#define TRACK_D 0.3f

// 速度参数
#define BASE_SPEED_STRAIGHT 3000   // 直道基础速度
#define BASE_SPEED_CURVE 2000      // 弯道基础速度
#define MAX_STEER 2000             // 最大转向差速

void gray_init()
{
    // 初始化灰度传感器引脚（D1-D5）
    gpio_init(GPIOA, DL_GPIO_PIN_21, PA21, IN_UP);   // D1 - 最左
    gpio_init(GPIOA, DL_GPIO_PIN_22, PA22, IN_UP);   // D2 - 左中
    gpio_init(GPIOA, DL_GPIO_PIN_23, PA23, IN_UP);   // D3 - 中间
    gpio_init(GPIOA, DL_GPIO_PIN_24, PA24, IN_UP);   // D4 - 右中
    gpio_init(GPIOA, DL_GPIO_PIN_25, PA25, IN_UP);   // D5 - 最右
    
    // 初始化循迹PID
    pid_init(&track_pid, POSITION_PID, TRACK_P, TRACK_I, TRACK_D);
    pid_set_limit(&track_pid, 500, MAX_STEER);
}

// 更新转向计时器（在定时器中断中调用）
void update_turn_timer() {
    if (turn_state != TURN_NONE) {
        turn_timer++;
    }
}

// 计算循迹偏差
// 将5个传感器的位置编码为-100~100的偏差值
// 传感器布局: D1(-2) D2(-1) D3(0) D4(1) D5(2)
// 权重: 越靠近边缘权重越大
static int16_t calc_track_error(void)
{
    uint8_t d1 = D1, d2 = D2, d3 = D3, d4 = D4, d5 = D5;
    int16_t error = 0;
    uint8_t valid_count = 0;
    
    // 加权计算偏差
    // D1: -100, D2: -50, D3: 0, D4: 50, D5: 100
    if(d1) { error += -100; valid_count++; }
    if(d2) { error += -50;  valid_count++; }
    if(d3) { error += 0;    valid_count++; }
    if(d4) { error += 50;   valid_count++; }
    if(d5) { error += 100;  valid_count++; }
    
    if(valid_count > 0) {
        error = error / valid_count;  // 取平均偏差
    }
    
    return error;
}

// 检测赛道类型
static void detect_track_type(void)
{
    uint8_t d1 = D1, d2 = D2, d3 = D3, d4 = D4, d5 = D5;
    uint8_t sum = d1 + d2 + d3 + d4 + d5;
    
    // 全白检测（所有传感器都在白色区域 - 可能是弯道或出线）
    if(sum == 0) {
        all_white_count++;
        if(all_white_count > 3) {
            // 根据上一次的偏差方向判断是左弯还是右弯
            if(track_error < 0) {
                current_track = TRACK_LEFT_CURVE;
            } else {
                current_track = TRACK_RIGHT_CURVE;
            }
        }
    } else {
        all_white_count = 0;
    }
    
    // 全黑检测（所有传感器都在黑线上 - 可能是十字交叉）
    if(sum == 5) {
        all_black_count++;
        if(all_black_count > 2) {
            current_track = TRACK_CROSS;
        }
    } else {
        // 如果只有中间3个传感器检测到黑线，认为是直道
        if(d2 && d3 && d4 && !d1 && !d5) {
            current_track = TRACK_STRAIGHT;
        }
        // 如果只有中间传感器检测到，也是直道
        else if(d3 && !d1 && !d5) {
            current_track = TRACK_STRAIGHT;
        }
        all_black_count = 0;
    }
}

// PID循迹控制（主控循环中调用）
void track_pid_control(void)
{
    uint8_t d1 = D1, d2 = D2, d3 = D3, d4 = D4, d5 = D5;
    uint8_t sum = d1 + d2 + d3 + d4 + d5;
    int16_t error;
    float pid_out;
    int base_speed;
    int left_speed, right_speed;
    
    // 检测赛道类型
    detect_track_type();
    
    // 根据赛道类型选择基础速度
    if(current_track == TRACK_STRAIGHT) {
        base_speed = BASE_SPEED_STRAIGHT;
    } else {
        base_speed = BASE_SPEED_CURVE;
    }
    
    // 计算循迹偏差
    error = calc_track_error();
    track_error = error;
    
    // 特殊情况处理
    if(sum == 0) {
        // 全白：所有传感器都离线了，根据上次偏差方向强行转向
        if(track_error < 0) {
            // 上次偏左，说明是左弯，继续左转
            pid_control(base_speed/2, base_speed);
        } else {
            // 上次偏右，说明是右弯，继续右转
            pid_control(base_speed, base_speed/2);
        }
        return;
    }
    
    if(sum == 5) {
        // 全黑：十字交叉或停车线，直行通过
        pid_control(base_speed, base_speed);
        return;
    }
    
    // PID计算转向输出
    track_pid.target = 0;
    track_pid.now = error;
    pid_cal(&track_pid);
    pid_out = track_pid.out;
    
    // 计算左右电机速度
    left_speed = base_speed - (int)pid_out;
    right_speed = base_speed + (int)pid_out;
    
    // 限幅
    if(left_speed < 0) left_speed = 0;
    if(right_speed < 0) right_speed = 0;
    if(left_speed > MAX_DUTY) left_speed = MAX_DUTY;
    if(right_speed > MAX_DUTY) right_speed = MAX_DUTY;
    
    // 输出到电机
    pid_control(left_speed, right_speed);
}

// 循迹主逻辑（兼容旧接口）
void track() {
    track_pid_control();
}

// 读取单个灰度传感器值
unsigned char digtal(unsigned char channel)
{
    char value = 0;
    switch(channel) 
    {
        case 1:  value = gpio_get(GPIOA, DL_GPIO_PIN_21) ? 1 : 0; break;  // D1
        case 2:  value = gpio_get(GPIOA, DL_GPIO_PIN_22) ? 1 : 0; break;  // D2
        case 3:  value = gpio_get(GPIOA, DL_GPIO_PIN_23) ? 1 : 0; break;  // D3
        case 4:  value = gpio_get(GPIOA, DL_GPIO_PIN_24) ? 1 : 0; break;  // D4
        case 5:  value = gpio_get(GPIOA, DL_GPIO_PIN_25) ? 1 : 0; break;  // D5
        default: value = 1; break;
    }
    return value; 
}

// 调试显示
void track_debug_display(void)
{
    OLED_ShowString(3, 1, "Err:");
    OLED_ShowSignedNum(3, 5, track_error, 3);
    
    OLED_ShowString(4, 1, "Trk:");
    switch(current_track) {
        case TRACK_STRAIGHT: OLED_ShowString(4, 5, "ST "); break;
        case TRACK_LEFT_CURVE: OLED_ShowString(4, 5, "LC "); break;
        case TRACK_RIGHT_CURVE: OLED_ShowString(4, 5, "RC "); break;
        case TRACK_CROSS: OLED_ShowString(4, 5, "CR "); break;
        default: OLED_ShowString(4, 5, "UN "); break;
    }
}
