#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "EC11.h"
#include <stdbool.h>
#define  EC11_GPIO_Pin_3  GPIO_Pin_3

#define  EC11_GPIO_Pin_4  GPIO_Pin_4

#define  EC11_GPIO  GPIOB

uint8_t KeyNum;		//定义用于接收按键键码的变量
int dir = 0;
int main(void)
{
	/*模块初始化*/
	LED_Init();		//LED初始化
	Key_Init();		//按键初始化
	LED1_ON();			//LED1翻转
    OLED_Init();

    OLED_ShowString(1, 3, "HelloWorld!");	//1行3列显示字符串HelloWorld!
    
 
    
   


    while (1) 
    {    
        
        
        KeyNum = Key_GetNum();		//获取按键键码
		
		if (KeyNum == 1)			//按键1按下
		{
			LED1_Turn();			//LED1翻转
		}
    }
 
}
        
        
        
     

