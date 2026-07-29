#include "TrackModule.h"
/*=============================================================================*
 * �ɵ���������																   *
 *=============================================================================*/
// ת��ǶȲ���
float Turn90Angle  = 80;   // ֱ����ת�����
float TurnMaxAngle = 65;   // �����ת�����
float TurnMidAngle = 40;   // �е�ת�����������ʱʹ�ã�
float TurnMinAngle = 15;   // ΢��ת�����
// �ٶȲ���
float BaseSpeed = 250;      // ����Ѳ���ٶȣ�ֱ��ʱ���ٶȣ�
float ForwardLimit = 50;		//ǰ������(ת����ڸ�ֵ������ǰ��)
u8 Track_Run = 0;           // Ѳ�߿��أ�Ĭ�ϴ����ȴ�����
volatile u32 Track_Run_TimeMs = 0;
volatile u8 Track_Finish_Flag = 0;
/*=============================================================================*
 * ������״̬����--ʶ�𵽺���ʱΪ1											   *
 *=============================================================================*/
typedef enum {
    STATE_CROSS         = 0,    // 0000 - ʮ��·��
    STATE_LEFT_90_A     = 1,    // 0001 - ��ֱ����
	STATE_LEFT_90_B		= 3,	// 0011
    STATE_RIGHT_90_A    = 8,  	// 1000 - ��ֱ����
	STATE_RIGHT_90_B    = 12,	// 1100
    STATE_LEFT_BIG      = 7,    // 0111 - �����
    STATE_RIGHT_BIG     = 14,   // 1110 - �Ҵ���
    STATE_LEFT_SMALL    = 11,   // 1011 - ��΢��
    STATE_RIGHT_SMALL   = 13,   // 1101 - ��΢��
    STATE_STRAIGHT      = 9,    // 1001 - ֱ��
    STATE_LOST          = 15    // 1111 - ����
} SensorState_t;

float base_speed_mm = 0;// �����ٶȣ�mm/s��
float turn_diff = 0;    // ת�����

/*=============================================================================*
 * Ѳ�߹��ܺ�������������Ŀ���ٶȣ�											   *
 *=============================================================================*/
void IRDM_line_inspection(void)
{
    static int last_state = STATE_STRAIGHT;// ��¼��һ�ε�״̬
    static u16 start_arm_delay_ms = 0;
    static u16 cross_hold_ms = 0;
	float left_motor_speed = 0;// ������ʱ�ٶȣ�m/s��
    float right_motor_speed = 0;// �ҵ����ʱ�ٶȣ�m/s��

    if (Track_Run == 0)
    {
        turn_diff = 0;
        base_speed_mm = 0;
        MotorA.Target_Encoder = 0;
        MotorB.Target_Encoder = 0;
        start_arm_delay_ms = 0;
        cross_hold_ms = 0;
        return;
    }

    Track_Run_TimeMs++;
    if (start_arm_delay_ms < 800)
    {
        start_arm_delay_ms++;
    }
    
    // ��ȡ������״̬��4�����������ֵ
    int sensor_state = (DH1 << 3) | (DH2 << 2) | (DH3 << 1) | DH4;

    if (start_arm_delay_ms >= 800)
    {
        if (sensor_state == STATE_CROSS)
        {
            if (++cross_hold_ms > 20)
            {
                Track_Run = 0;
                Track_Finish_Flag = 1;
                turn_diff = 0;
                base_speed_mm = 0;
                MotorA.Target_Encoder = 0;
                MotorB.Target_Encoder = 0;
                return;
            }
        }
        else
        {
            cross_hold_ms = 0;
        }
    }
    /*=========================================================================*
     * ״̬�жϣ�����ת�����												   *
     *=========================================================================*/
    switch (sensor_state)
    {
       case STATE_CROSS:// ����·�ڴ���
			turn_diff = 0;
            break;
        case STATE_LEFT_90_A: // ��ֱ����
		case STATE_LEFT_90_B: // ��ֱ����
            turn_diff = Turn90Angle;
            break;
        case STATE_RIGHT_90_A: // ��ֱ����
		case STATE_RIGHT_90_B: // ��ֱ����
            turn_diff = -Turn90Angle;
            break;
        case STATE_LEFT_BIG://�����
            turn_diff = TurnMaxAngle;
            break;
        case STATE_RIGHT_BIG://�Ҵ���
            turn_diff = -TurnMaxAngle;
            break;
        case STATE_LEFT_SMALL://��΢��
            turn_diff = TurnMinAngle;
            break;
        case STATE_RIGHT_SMALL://��΢��
            turn_diff = -TurnMinAngle;
            break;
        case STATE_STRAIGHT://ֱ��
            turn_diff = 0;
            break;
        case STATE_LOST://���ߴ���
            turn_diff = 0;
            if (last_state == STATE_LEFT_SMALL) turn_diff = TurnMidAngle;//������ת
			else if (last_state == STATE_RIGHT_SMALL) turn_diff = -TurnMidAngle;//������ת
			else if(last_state == STATE_LEFT_BIG ) turn_diff = TurnMaxAngle;//������ת
			else if(last_state == STATE_RIGHT_BIG ) turn_diff = -TurnMaxAngle;//������ת
            break;
        default: // δ����״̬��ֱ��
            turn_diff = 0;
            break;
    }
	//���洫����״̬
	if(sensor_state!=STATE_LOST)
	{
		last_state=sensor_state;
	}
	// ת���ٶ�Խ�󣬻����ٶ�Խ��
	if(fabs(turn_diff)<ForwardLimit)
	{
		base_speed_mm = BaseSpeed - (BaseSpeed * (fabs(turn_diff) / ForwardLimit));
	}
	else base_speed_mm=0;
    /*========================================================================*
     * ���õ��Ŀ���ٶȣ���-ת����٣���+ת����٣���λ��mm/s��                   *
     *=========================================================================*/
	left_motor_speed = 0.001f * (base_speed_mm - turn_diff); 
    right_motor_speed = 0.001f * (base_speed_mm + turn_diff);
    // ��ֵ�����Ŀ���ٶ�
    MotorA.Target_Encoder = left_motor_speed;//����
    MotorB.Target_Encoder = right_motor_speed;//�ҵ��
}

void TrackModule_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ�� GPIOA �� GPIOB ʱ��，C8T6 上這些引脚可用
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    // 配置 PA4/PA5 為下拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // 下拉输入模式
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // 配置 PB12/PB13 為下拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // 下拉输入模式
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
















