#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;		//定义用于接收按键键码的变量
//2023年12月18日15点51分--运行成功
int main(void)
{
	LED_Init();		//LED初始化
	Key_Init();		//按键初始化
	LED1_ON();			//LED1翻转
    
	while (1)
	{
		KeyNum = Key_GetNum();		//获取按键键码
		
		if (KeyNum == 1)			//按键1按下
		{
			LED1_Turn();			//LED1翻转
		}
		
	}
}
