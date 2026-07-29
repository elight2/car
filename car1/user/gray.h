#ifndef __gray_track_h_
#define __gray_track_h_
#include "headfile.h"

// 灰度传感器宏定义（1=检测到黑线，0=检测到白色）
#define D1 1-digtal(1)
#define D2 1-digtal(2)
#define D3 1-digtal(3)
#define D4 1-digtal(4)
#define D5 1-digtal(5)

// 转向状态枚举
typedef enum {
    TURN_NONE = 0,        // 不转向
    TURN_LEFT_SMALL,      // 小角度左转
    TURN_RIGHT_SMALL,     // 小角度右转
    TURN_LEFT_LARGE,      // 大角度左转
    TURN_RIGHT_LARGE,     // 大角度右转
    TURN_LEFT_CROSS,      // 十字弯左转
    TURN_RIGHT_CROSS,     // 十字弯右转
} TurnState;

// 赛道类型枚举
typedef enum {
    TRACK_STRAIGHT = 0,   // 直道
    TRACK_LEFT_CURVE,     // 左弯
    TRACK_RIGHT_CURVE,    // 右弯
    TRACK_CROSS,          // 十字/交叉
    TRACK_STOP,           // 停车
} TrackType;

extern TurnState turn_state;
extern uint32_t turn_timer;
extern int16_t track_error;       // 循迹偏差（-100~100）
extern uint8_t all_white_count;   // 全白计数（用于弯道检测）
extern uint8_t all_black_count;   // 全黑计数（用于十字检测）
extern TrackType current_track;   // 当前赛道类型

void gray_init(void);
void track(void);
void track_pid_control(void);     // PID循迹控制
unsigned char digtal(unsigned char channel);
void update_turn_timer(void);
void track_debug_display(void);   // 调试显示

#endif
