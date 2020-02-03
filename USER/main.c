#include "main.h"
int cou=0;
/**********************************************************
新板子的引脚变化
遥控器(未变)PB7
CAN通信 (有变)PB8/CAN1_RX  PB9/CAN1_TX   已改
激光 PB0/TIM3  CH3
预留（两个IO，一个串口） 串口PA2/USART2_TX PA3/USART2_RX  PA7/IO  PA6/RST
串口3，6不变  
时钟通道 PA1/TIM5_CH2   PA0/TIM5_CH1   PB5/TIM3_CH2
最重要的一个：记录程序运行时间的定时器改了，由TIM5变为TIM2
**********************************************************/
/**********************************************************
窗口看门狗
有一个7位的递减计数器，当喂狗的时候计数器的值大于设定值时，或者
当计数器的值从0x40变为0x3F时，看门狗都会复位
如果使能看门狗而且允许中断，当计数器的值变为0x40时候，就会产生一个中断
可以喂狗，避免系统复位
**********************************************************/

int i=0;
int main()
{
  delay_ms(2000);
	engineerpower_Init();
	BSP_Init();

	ControtLoopTaskInit();

	RemoteTaskInit();
	delay_ms(1000);

	TIM6_Start();
	//WWDG_Init();

	delay_ms(100);

	while(1)
	{
	
	  delay_ms(1);
		

		cou++;

	}
}
