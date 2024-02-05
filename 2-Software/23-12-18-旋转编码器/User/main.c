#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "EC11.h"
#include <stdbool.h>
uint8_t KeyNum;		//定义用于接收按键键码的变量
int flag = 0;  //标志位
bool CW_1 = 0;
bool CW_2 = 0;
int dir =0;
int keynum =0;
int main(void)
{
	/*模块初始化*/
	LED_Init();		//LED初始化
	Key_Init();		//按键初始化
	LED1_ON();			
    OLED_Init();

    OLED_ShowString(1, 1, "---HelloWorld---");	
    OLED_ShowString(2, 1, "dir:");	
    OLED_ShowNum(2,5,dir,2);
    OLED_ShowString(3, 1, "keynum:");	
    OLED_ShowNum(3,8,keynum,2);
    while (1) 
    {    
        KeyNum = Key_GetNum();		//获取按键键码
		if (KeyNum == 1)			//按键1按下
		{
			LED1_Turn();			//LED1翻转
            keynum++;
            OLED_ShowNum(3,8,keynum,2);
		}
        
        int alv = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3);
        int blv = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4);
          if (flag == 0 && alv == 0) {
              
                CW_1 = blv;
                flag = 1;
                OLED_ShowString(4, 1, "CW_1 = blv");	
              }
              if (flag && alv) {
                CW_2 = !blv;  //取反是因为 alv,blv必然异步，一高一低。
                if (CW_1 && CW_2) {
                  dir++;
                    OLED_ShowNum(2,1,dir,2);
                }
                if (CW_1 == false && CW_2 == false) {
                   dir--;
                    OLED_ShowNum(2,1,dir,2);
                }
                flag = 0;
          }
        
        
    }
 
}
        
        
        
     

