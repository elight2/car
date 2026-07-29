#ifndef __TRACKMODULE_H
#define __TRACKMODULE_H
#include "sys.h"

#define DH4 PBin(8)
#define DH3 PCin(9)
#define DH2 PCin(4)
#define DH1 PCin(8)
extern float Turn90Angle ;   // ֱ����ת��Ƕ�
extern float TurnMaxAngle;   // �����ת��Ƕ�
extern float TurnMidAngle;   // �е�ת��Ƕȣ�����ʱʹ�ã�
extern float TurnMinAngle;   // ΢��ת��Ƕ�
extern float BaseSpeed;
extern float ForwardLimit;
// �ٶȲ�������λ��m/s��
extern float base_speed_mm ;        // �����ٶȣ�mm/s��
extern float turn_diff ;            // ת����٣���+��-����λ��mm/s��
extern u8 Track_Run;                // Ѳ�߿���ʹ�ܱ�־��1��ʾ����
extern volatile u32 Track_Run_TimeMs;   // Ѳ�߼�ʱ����λms
extern volatile u8 Track_Finish_Flag;    // Ѳ����ɱ�־

void TrackModule_Init(void);
void IRDM_line_inspection(void);
#endif

