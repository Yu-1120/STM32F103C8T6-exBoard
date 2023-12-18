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
    
    
    
   
	//2023年12月18日--旋转编码器的左右转的旋转有问题
    uint32_t count = 0;
    uint32_t wait_t = 0;
    bool encoder_switch = 0;
    uint8_t encoder_a_pre = GPIO_ReadInputDataBit(GPIOB, EC11_GPIO_Pin_4);
    uint8_t encoder_b_pre = GPIO_ReadInputDataBit(GPIOB, EC11_GPIO_Pin_3);
    int32_t steps = 0;

    while (1) {
        
        KeyNum = Key_GetNum();		//获取按键键码
		
		if (KeyNum == 1)			//按键1按下
		{
			LED1_Turn();			//LED1翻转
		}
    uint8_t encoder_a = GPIO_ReadInputDataBit(EC11_GPIO, EC11_GPIO_Pin_3);
    uint8_t encoder_b = GPIO_ReadInputDataBit(EC11_GPIO, EC11_GPIO_Pin_4);
    OLED_ShowNum(2, 1, steps, 5);	
    if (encoder_a_pre != encoder_a && encoder_switch) {
      wait_t = 5;
      encoder_switch = true;
    }
 
      //a 0->1, b 0 Clockwise; b 1 AntiClockwise
      if (encoder_a == 1) {
        if (encoder_b == 0) {
            		//2行1列显示十进制数字12345，长度为5
          steps++;
        } else {
           OLED_ShowNum(2, 1, steps, 5);	
          steps--;
            OLED_ShowNum(2, 1, steps, 5);
        }
    
        if (encoder_b == 1) {
          steps++;
            OLED_ShowNum(2, 1, steps, 5);
        } else {
          steps--;
            OLED_ShowNum(2, 1, steps, 5);
        }
      }
      encoder_switch = false;
      encoder_a_pre = encoder_a;
     // printf("%d\r\n", steps);
    }
 
}
        
        
        
     

