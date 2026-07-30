#include "headfile.h"
#include "key.h"
int KeyNum=0;
/**
  * 函    数：按键获取键码
  * 参    数：无
  * 返 回 值：按下按键的键码值，范围：0~2，返回0代表没有按键按下
  * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
  */

void Key_Init(void) {
    gpio_init(GPIOB, KEY1_PIN, PB3, IN_UP);  // 按钮1（PB3）
    gpio_init(GPIOB, KEY2_PIN, PB2, IN_UP);  // 按钮2（PB2）
}

int Key_GetNum() {
    static uint8_t key1_state = 0, key2_state = 0;
    int num = 0;

    // 检测按钮1（PB3）
    if (gpio_get(GPIOB, KEY1_PIN) == 0) {
        if (key1_state == 0) {
            delay_ms(20);
            if (gpio_get(GPIOB, KEY1_PIN) == 0) {
                key1_state = 1;
                num = 1;				// 按钮1按下

            }
        }
    } else {
        key1_state = 0;
    }

    // 检测按钮2（PB2）
    if (gpio_get(GPIOB, KEY2_PIN) == 0) {
        if (key2_state == 0) {
            delay_ms(20);
            if (gpio_get(GPIOB, KEY2_PIN) == 0) {
                key2_state = 1;
                num = 2;  // 按钮2按下
            }
        }
    } else {
        key2_state = 0;
    }

    return num;
}