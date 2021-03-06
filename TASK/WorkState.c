#include "main.h"
WorkState_e lastWorkState = STOP_STATE;
WorkState_e workState = STOP_STATE;
uint8_t camera_temp = 0;
uint8_t dafu_temp = 0;
uint8_t cat_temp = 0;    
//int identify_flag =0 ;      //用于设置是否为战车识别模式
/**
函数：WorkStateFSM()
功能：控制工作模式
**/
/////////////////////以下是立flag的区域
int flag_prepare_ready=0;
int flag_Dafu_fromsight=1;//0;//从视觉方面接收到了大幅数据
////////////////////
void WorkStateFSM(void)
{
	lastWorkState = workState;//更新当前工作状态
	switch(workState)
	{
		case STOP_STATE:                            
		{
			if(GetInputMode() != STOP)//遥控器强制停止
			{
				workState = PREPARE_STATE;   //取消急停要先过抖�
			}
		}break;
		
		case PREPARE_STATE://准备状态
		{
			if(GetInputMode() == STOP)//遥控器强制停止
			{
				workState = STOP_STATE;
			}
			else if(time_tick_1ms > PREPARE_TIME_TICK_MS)//准备状态达到指定时间后，转到操作手控制状态
			{
				workState = NORMAL_STATE;
			}
		}break;
		case NORMAL_STATE:     //操作手控制状态（有输入）
		{
			if(GetInputMode() == STOP)//遥控器强制停止
			{
				workState = STOP_STATE;
			}
//			else if(camera_temp == 1)//摁下c键，进入打大符模式
//			{
////       S1inputmode = ZIMIAO;
//			}
			else if(dafu_temp == 1&&flag_Dafu_fromsight==1)//摁下f键，转到无输入状态    (打大福) 
			{
				workState = CAMERA_STATE;//STANDBY_STATE;      
			}	
			else if(cat_temp == 1)//遥控器、键盘无输入，转到无输入状态     
			{
				workState = CATWALK_STATE;///CAMERA_STATE;//STANDBY_STATE;      
			}	
		}break;
		
		case CAMERA_STATE:      //大符状态
		{
			if(GetInputMode() == STOP)//遥控器强制停止
			{
				workState = STOP_STATE;
			}	
			else if(dafu_temp == 0)//松开C键，进入底盘不动状态
			{
				workState = NORMAL_STATE;      
			}
		}break;
	
		case ADJUST_STATE:      //瞄准状态
		{
//			if(GetInputMode() == STOP)
//			{
//				workState = STOP_STATE;
//			}
//			else if(adjust_temp == 0)
//			{
//				workState = NORMAL_STATE;      
//			}
		}break;
		
		case CATWALK_STATE:      
		{
			if(GetInputMode() == STOP)
			{
				workState = STOP_STATE;
			}
			else if(cat_temp == 0)
			{
				workState = NORMAL_STATE;      
			}
		}break;
		default:
		{
		}
	}	
}

/**
函数：WorkStateSwitchProcess()
功能：如果从其他模式切换到prapare模式，要将一系列参数初始化
**/
void WorkStateSwitchProcess(void)
{
	if((lastWorkState != workState) && (workState == PREPARE_STATE))  
	{
		ControtLoopTaskInit();
		RemoteTaskInit();
		ChassisMotorInit();
		//AllDataInit();
	}
}
/**
函数：SetWorkState(WorkState_e state)
功能：返回当前工作状态

**/
void SetWorkState(WorkState_e state)
{
	if(workState != PREPARE_STATE)
	{
    workState = state;
	}
}

/**
函数：WorkState_e GetWorkState(void)
功能：设置工作状态

**/
WorkState_e GetWorkState(void)
{
	return workState;
}

WorkState_e GetlastWorkState(void)
{
	return lastWorkState;
}

void AllDataInit(void)
{
	Key_State cameraKey = KEY_INIT;//zimiao�
	Key_State dafuKey = KEY_INIT;//大符键
	Key_State servoKey = KEY_INIT;//舵机键
	Key_State frictionKey = KEY_INIT;//摩擦轮速度切换键
	uint8_t mouseLeftPress = 0;
	uint8_t continuous_shoot_Flag = 0;
	uint8_t quickShootFlag = 0;
	uint8_t servoPositionFlag = 0;
	uint8_t sendCustomDataFlag = 0;
	uint8_t camera_temp = 0;
	uint8_t dafu_temp = 0;
	uint8_t cat_temp = 0;
	Key_State xtl = KEY_INIT;//XTL
}
