#include "stm32f10x.h"
#include "USART.h"
#include "Delay.h"
#include "string.h"
#include "LED.h"
#include "Beep.h"
uint8_t KeyNum;		//定义用于接收按键键码的变量
int main(void)
{
    /*模块初始化*/
    LED_Init();		//LED初始化
    LED1_OFF();			//LED1翻转
    BEEP_Init();
    Sound(500);//尖锐 //要加for循环不然没效果
    while (1)
    {

        //play_music();
    }
}

