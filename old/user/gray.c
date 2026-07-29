#include"headfile.h"
// 全局变量定义
TurnState turn_state = TURN_NONE;
uint32_t turn_timer = 0;

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
    const uint32_t SMALL_TURN_DURATION = 150;
    // 大角度转向持续时间(ms)
    const uint32_t LARGE_TURN_DURATION = 800;

    switch(turn_state) {
        case TURN_LEFT_SMALL:
            pid_control(-3, -1);  // 小左转（左慢右快）
            if (turn_timer >= SMALL_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        case TURN_RIGHT_SMALL:
            pid_control(-1, -3);  // 小右转（左快右慢）
            if (turn_timer >= SMALL_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        case TURN_LEFT_LARGE:
            pid_control(-5, -1);  // 大左转（左快右慢，角度更大）
            if (turn_timer >= LARGE_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        case TURN_RIGHT_LARGE:
            pid_control(-1, -5);  // 大右转（左慢右快，角度更大）
            if (turn_timer >= LARGE_TURN_DURATION) {
                turn_state = TURN_NONE;
                turn_timer = 0;
            }
            break;
        default:
            break;
    }
}

// 循迹主逻辑
void track() {
    // 如果正在转向，优先执行转向逻辑
    uint8_t d1 = D1, d2 = D2, d3 = D3, d4 = D4, d5 = D5;
	
			if (d1 + d2 != 2)  // 检查是否有传感器值为1
		{
			if (d1 == 0)  // 优先级最高
			{
				pid_control(3000,1000);
			}
			else if (d2 == 0)  // 优先级次之
			{
				pid_control(2000,1000);
			}

		}
		else if (d4 + d5 != 2)
		
		{
			if (d5 == 0)  // 优先级最高
			{
				pid_control(1000, 3000);
			}
			else if (d4 == 0)  // 优先级次之
			{
				pid_control(1000, 2000);
			}

		}
		
		else 
		{
			pid_control(1000,1000);
		}
		int count = 0;
		while(d1==1 && d2==1&& d3==1&&d4==1&&d5==1)
		{
			
			count++;
			if(count == 100)
			{
				pid_control(1500,0);

			}
			delay_ms(10);
			d1 = D1;
			d2 = D2;
			d3 = D3;
			d4 = D4;
			d5 = D5;
		}
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