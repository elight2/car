// 日期：2026-07-30 17:13 - 重写转向逻辑
#ifndef __gray_track_h_
#define __gray_track_h_
#include "headfile.h"

// 八路灰度传感器定义
// X1(最左) -> PB9
// X2      -> PA21
// X3      -> PA22
// X4      -> PA23
// X5      -> PA24
// X6      -> PA25
// X7      -> PA26
// X8(最右) -> PA27

// digtal() 返回：0=黑线，1=白线（gpio_get直接返回值）
// Dn 取反后：1=黑线，0=白线
#define D1 (1-digtal(1))   // X1 - PB9  最左
#define D2 (1-digtal(2))   // X2 - PA21
#define D3 (1-digtal(3))   // X3 - PA22
#define D4 (1-digtal(4))   // X4 - PA23
#define D5 (1-digtal(5))   // X5 - PA24
#define D6 (1-digtal(6))   // X6 - PA25
#define D7 (1-digtal(7))   // X7 - PA26
#define D8 (1-digtal(8))   // X8 - PA27  最右

void gray_init(void);
void track(void);
unsigned char digtal(unsigned char channel);

#endif
