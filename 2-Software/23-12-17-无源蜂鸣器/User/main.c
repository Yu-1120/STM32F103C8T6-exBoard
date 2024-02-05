#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Beep.h"
uint8_t KeyNum;		//定义用于接收按键键码的变量
int main(void)
{
	/*模块初始化*/
	LED_Init();		//LED初始化
	Key_Init();		//按键初始化
	LED1_OFF();			//LED1翻转
    BEEP_Init();
	while (1)
	{
			
        play_music();
	}
}
