#include"headfile.h"

// 全局变量定义
TurnState turn_state = TURN_NONE;
uint32_t turn_timer = 0;

// 优化后的循迹参数
#define BASE_SPEED 2500        // 基础速度
#define TURN_SPEED_RATIO 0.7   // 转弯速度比例
#define CORNER_SPEED_RATIO 0.5 // 直角转弯速度比例
#define STRAIGHT_SPEED 2800    // 直线速度

void gray_init()
{
    // 初始化灰度传感器引脚（D1-D5）
    gpio_init(GPIOA, DL_GPIO_PIN_21, PA21, IN_UP);   // D1
    gpio_init(GPIOA, DL_GPIO_PIN_22, PA22, IN_UP);  // D2
    gpio_init(GPIOA, DL_GPIO_PIN_23, PA23, IN_UP);   // D3
    gpio_init(GPIOA, DL_GPIO_PIN_24, PA24, IN_UP);  // D4
    gpio_init(GPIOA, DL_GPIO_PIN_25, PA25, IN_UP);  // D5
}

// 更新转向计时器（在定时器中断中调用）
void update_turn_timer() {
    if (turn_state != TURN_NONE) {
        turn_timer++;
    }
}

// 处理转向逻辑
static void handle_turn() {
    // 小角度转向持续时间(ms)
    const uint32_t SMALL_TURN_DURATION = 100;
    // 大角度转向持续时间(ms)
    const uint32_t LARGE_TURN_DURATION = 300;
    // 直角转向持续时间(ms)
    const uint32_t CORNER_TURN_DURATION = 200;

    switch(turn_state) {
        case TURN_LEFT_SMALL:
            pid_control(BASE_SPEED * TURN_SPEED_RATIO, BASE_SPEED);  // 小左转（左慢右快）
            if (turn_timer >= SMALL_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        case TURN_RIGHT_SMALL:
            pid_control(BASE_SPEED, BASE_SPEED * TURN_SPEED_RATIO);  // 小右转（左快右慢）
            if (turn_timer >= SMALL_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        case TURN_LEFT_LARGE:
            pid_control(BASE_SPEED * CORNER_SPEED_RATIO, BASE_SPEED);  // 大左转
            if (turn_timer >= LARGE_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        case TURN_RIGHT_LARGE:
            pid_control(BASE_SPEED, BASE_SPEED * CORNER_SPEED_RATIO);  // 大右转
            if (turn_timer >= LARGE_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        case TURN_LEFT_CORNER:
            pid_control(BASE_SPEED * CORNER_SPEED_RATIO, BASE_SPEED * 1.2);  // 左直角
            if (turn_timer >= CORNER_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        case TURN_RIGHT_CORNER:
            pid_control(BASE_SPEED * 1.2, BASE_SPEED * CORNER_SPEED_RATIO);  // 右直角
            if (turn_timer >= CORNER_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        default:
            break;
    }
}

// 优化的循迹主逻辑
void track() {
    // 如果正在转向，优先执行转向逻辑
    if (turn_state != TURN_NONE) {
        handle_turn();
        return;
    }
    
    uint8_t d1 = D1, d2 = D2, d3 = D3, d4 = D4, d5 = D5;
    
    // 传感器位置权重（用于计算偏差）
    const int sensor_weights[] = {-2, -1, 0, 1, 2};
    int position_error = 0;
    int active_sensors = 0;
    
    // 计算位置误差
    if (d1 == 0) { position_error -= 2; active_sensors++; }
    if (d2 == 0) { position_error -= 1; active_sensors++; }
    if (d3 == 0) { position_error += 0; active_sensors++; }
    if (d4 == 0) { position_error += 1; active_sensors++; }
    if (d5 == 0) { position_error += 2; active_sensors++; }
    
    // 根据传感器状态执行不同的循迹策略
    if (active_sensors == 0) {
        // 所有传感器都未检测到黑线，可能是直线丢失或十字路口
        pid_control(STRAIGHT_SPEED, STRAIGHT_SPEED);
        return;
    }
    
    // 计算速度和转向
    int left_speed, right_speed;
    
    if (position_error == 0) {
        // 在中心线上，直线前进
        left_speed = STRAIGHT_SPEED;
        right_speed = STRAIGHT_SPEED;
    } else if (abs(position_error) == 1) {
        // 轻微偏差，小角度修正
        int speed_diff = position_error * 300;  // 修正系数
        left_speed = STRAIGHT_SPEED + speed_diff;
        right_speed = STRAIGHT_SPEED - speed_diff;
    } else if (abs(position_error) == 2) {
        // 中等偏差，中等角度修正
        int speed_diff = position_error * 500;  // 修正系数
        left_speed = STRAIGHT_SPEED + speed_diff;
        right_speed = STRAIGHT_SPEED - speed_diff;
    } else {
        // 大偏差或多个传感器同时触发
        if (d1 == 0 && d2 == 0) {
            // 左急转
            turn_state = TURN_LEFT_LARGE;
            turn_timer = 0;
            left_speed = BASE_SPEED * CORNER_SPEED_RATIO;
            right_speed = BASE_SPEED * 1.2;
        } else if (d4 == 0 && d5 == 0) {
            // 右急转
            turn_state = TURN_RIGHT_LARGE;
            turn_timer = 0;
            left_speed = BASE_SPEED * 1.2;
            right_speed = BASE_SPEED * CORNER_SPEED_RATIO;
        } else {
            // 默认直线
            left_speed = STRAIGHT_SPEED;
            right_speed = STRAIGHT_SPEED;
        }
    }
    
    // 限制速度范围
    left_speed = (left_speed < 0) ? 0 : (left_speed > 3500) ? 3500 : left_speed;
    right_speed = (right_speed < 0) ? 0 : (right_speed > 3500) ? 3500 : right_speed;
    
    pid_control(left_speed, right_speed);
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