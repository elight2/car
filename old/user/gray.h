#ifndef __gray_track_h_
#define __gray_track_h_
#include "headfile.h"

#define D1 1-digtal(1)
#define D2 1-digtal(2)
#define D3 1-digtal(3)
#define D4 1-digtal(4)
#define D5 1-digtal(5)

// 转向状态枚举（补充完整所有转向类型）
typedef enum {
    TURN_NONE,        // 不转向
    TURN_LEFT_SMALL,  // 小角度左转
    TURN_RIGHT_SMALL, // 小角度右转
    TURN_LEFT_LARGE,  // 大角度左转（新增）
    TURN_RIGHT_LARGE  // 大角度右转（新增）
} TurnState;

extern TurnState turn_state;
extern uint32_t turn_timer;

void gray_init(void);
void track(void);
unsigned char digtal(unsigned char channel);
void update_turn_timer(void);

#endif
