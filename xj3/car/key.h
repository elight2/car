
#ifndef __key_h_
#define __key_h_

#include "headfile.h"

#define KEY1_PIN DL_GPIO_PIN_3  // PB3
#define KEY2_PIN DL_GPIO_PIN_2  // PB2£¨Ô­PB4¸ÄÎªPB2£©
void Key_Init(void);
int Key_GetNum(void);
extern int KeyNum;
#endif