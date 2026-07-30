#include "headfile.h"
#include "key.h"
int KeyNum=0;

void Key_Init(void) {
    gpio_init(GPIOB, KEY1_PIN, PB3, IN_UP);  // 单个按键（PB3）
}

int Key_GetNum() {
    static uint8_t key1_state = 0;
    int num = 0;

    // 检测按钮（PB3）
    if (gpio_get(GPIOB, KEY1_PIN) == 0) {
        if (key1_state == 0) {
            delay_ms(20);
            if (gpio_get(GPIOB, KEY1_PIN) == 0) {
                key1_state = 1;
                num = 1;  // 按键按下
            }
        }
    } else {
        key1_state = 0;
    }

    return num;
}
