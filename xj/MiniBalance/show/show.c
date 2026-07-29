/***********************************************
公司：轮趣科技(东莞)有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com 
速卖通: https://minibalance.aliexpress.com/store/4455017
版本：V1.0
修改时间：2022-09-05

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version: V1.0
Update：2022-09-05

All rights reserved
***********************************************/
#include "show.h"
/**************************************************************************
Function: OLED display
Input   : none
Output  : none
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void oled_show(void)
{
	memset(OLED_GRAM,0, 128*8*sizeof(u8));	//GRAM清零但不立即刷新，防止花屏
		//=============第一行显示小车模式=======================//
	OLED_ShowString(0,0,"IRDM:");
	if(DH1)  OLED_ShowString(50,0,"1");
	else     OLED_ShowString(50,0,"0");
	
	if(DH2)  OLED_ShowString(65,0,"1");
	else     OLED_ShowString(65,0,"0");
	
	if(DH3)  OLED_ShowString(80,0,"1");
	else     OLED_ShowString(80,0,"0");
	
	if(DH4)  OLED_ShowString(95,0,"1");
	else     OLED_ShowString(95,0,"0");
	
    OLED_ShowString(0,10,"Vx");
	OLED_ShowNumber(20,10,base_speed_mm,4,12);
	OLED_ShowString(60,10,"Vz");
	if(Move_Z<0) OLED_ShowString(80,10,"-");
	else OLED_ShowString(80,10,"+");
	OLED_ShowNumber(90,10,fabs(turn_diff),4,12);
	OLED_ShowNumber(0,20,Turn90Angle,3,12);
	OLED_ShowNumber(40,20,TurnMaxAngle,3,12);
	OLED_ShowNumber(80,20,TurnMidAngle,3,12);
	OLED_ShowNumber(100,20,TurnMinAngle,3,12);
								OLED_ShowString(00,30,"L-T:");
	if(MotorA.Target_Encoder<0)	OLED_ShowString(30,30,"-"),
							OLED_ShowNumber(36,30,-MotorA.Target_Encoder*1000,4,12);
	if(MotorA.Target_Encoder>=0)	OLED_ShowString(30,30,"+"),
								OLED_ShowNumber(36,30,MotorA.Target_Encoder*1000,4,12);
	OLED_ShowString(66,30,"L-E:");
	if(MotorA.Current_Encoder<0)	  	{OLED_ShowString(94,30,"-");OLED_ShowNumber(104,30,-MotorA.Current_Encoder*1000,4,12);}
	if(MotorA.Current_Encoder>=0)  	{OLED_ShowString(94,30,"+");OLED_ShowNumber(104,30,MotorA.Current_Encoder*1000,4,12);}
								OLED_ShowString(00,40,"R-T:");
	
	if(MotorB.Target_Encoder<0)	OLED_ShowString(30,40,"-"),
							OLED_ShowNumber(36,40,-MotorB.Target_Encoder*1000,4,12);
	if(MotorB.Target_Encoder>=0)	OLED_ShowString(30,40,"+"),
							OLED_ShowNumber(36,40,MotorB.Target_Encoder*1000,4,12);
	OLED_ShowString(66,40,"R-E:");
	if(MotorB.Current_Encoder<0)		{OLED_ShowString(94,40,"-");OLED_ShowNumber(104,40,-MotorB.Current_Encoder*1000,4,12);}
	if(MotorB.Current_Encoder>=0)  	{OLED_ShowString(94,40,"+");OLED_ShowNumber(104,40,MotorB.Current_Encoder*1000,4,12);}
	OLED_ShowString(0,50,"Volt:");
	OLED_ShowString(62,50,".");
	OLED_ShowString(86,50,"V");
	OLED_ShowNumber(48,50,Voltage/100,2,12);
	OLED_ShowNumber(70,50,(int)(Voltage/10)%10,1,12);//显示电压
	OLED_ShowNumber(78,50,(int)Voltage%10,1,12);
	if(EN==1)        OLED_ShowString(105,50, "OFF");
	else        	 OLED_ShowString(105,50, "ON ");
	
	
	
	OLED_Refresh_Gram();	
}


/**************************************************************************
Function: Send data to APP
Input   : none
Output  : none
函数功能：向APP发送数据
入口参数：无
返回  值：无
**************************************************************************/
void APP_Show(void)
{    
  static u8 flag;
	int Encoder_Left_Show,Encoder_Right_Show,Voltage_Show;
	Voltage_Show=(Voltage-1110)*2/3;		if(Voltage_Show<0)Voltage_Show=0;if(Voltage_Show>100) Voltage_Show=100;   //对电压数据进行处理
	Encoder_Right_Show=MotorB.Current_Encoder*1000; if(Encoder_Right_Show<0) Encoder_Right_Show=-Encoder_Right_Show;			  //对编码器数据就行数据处理便于图形化
	Encoder_Left_Show=MotorA.Current_Encoder*1000;  if(Encoder_Left_Show<0) Encoder_Left_Show=-Encoder_Left_Show;
	flag=!flag;
	if(PID_Send==1)			//发送PID参数,在APP调参界面显示
	{
		printf("{C%d:%d:%d:%d:%d:%d:%d:%d:%d}$",(int)Velocity_KP,(int)Velocity_KI,(int)(BaseSpeed),(int)(Turn90Angle),(int)(TurnMaxAngle),(int)(TurnMidAngle),(int)(TurnMinAngle),(int)ForwardLimit,0);//打印到APP上面	
		PID_Send=0;	
	}	
   else	if(flag==0)		// 发送电池电压，速度，角度等参数，在APP首页显示
	 {
		 printf("{A%d:%d:%d}$",(int)Encoder_Left_Show,(int)Encoder_Right_Show,(int)Voltage_Show); //打印到APP上面
	 }
	 else								//发送小车姿态角，在波形界面显示
	   printf("{B%d:%d:%d}$",(int)0,(int)0,(int)0); //可按格式自行增加显示波形，最多可显示五个
}



