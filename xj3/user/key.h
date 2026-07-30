#ifndef __key_h_
#define __key_h_

#include "headfile.h"

#define KEY1_PIN DL_GPIO_PIN_3  // PB3 - 单个按键，按下直接开机运行

void Key_Init(void);
int Key_GetNum(void);
extern int KeyNum;
#endif
