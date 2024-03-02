#include "stm32f10x.h"       
#include <stdbool.h>
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "EC11.h"

uint8_t KeyNum;		//定义用于接收按键键码的变量

int Encoder_Count  =0;
int keynum =0;
int main(void)
{
	LED_Init();		//LED初始化
	Key_Init();		//按键初始化
	LED1_ON();			
    OLED_Init();

    OLED_ShowString(1, 1, "---HelloWorld---");	
    OLED_ShowString(2, 1, "Count:");	
    OLED_ShowNum(2,7,Encoder_Count ,2);
    OLED_ShowString(3, 1, "keynum:");	
    OLED_ShowNum(3,8,keynum,2);
    
    int alv = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3);
    int blv = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4);
    while (1) 
    {    
        KeyNum = Key_GetNum();		//获取按键键码
		if (KeyNum == 1)			//按键1按下
		{
			LED1_Turn();			//LED1翻转
            keynum++;
            OLED_ShowNum(3,8,keynum,2);
		}
       
         if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)  !=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) ) 
         {
           if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 1 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0)
           {

          
                    Encoder_Count ++;
                    OLED_ShowNum(2,7,Encoder_Count ,2);
                    OLED_ShowString(4, 1, "++");	
               
           }
#if 1

           if ((GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 1) && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == 0))
            {
           
        
                    Encoder_Count --;
                    OLED_ShowNum(2,7,Encoder_Count ,2);
                    OLED_ShowString(4, 1, "--");	
               
            }


#endif           
           
        }


        
        
    }
 
}
        
        
        
     

