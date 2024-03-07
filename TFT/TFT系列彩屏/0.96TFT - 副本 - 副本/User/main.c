
//////////////////////////////////////////////////////////////////////////////////	 

/********************************** (C) COPYRIGHT ******************************* 


* File Name : Main.c 
* Author : B站:小昱君__ 
* Version : V1.0 
* Date : 2024年2月19日
* Description : 演示ST7735 硬件SPI驱动 
//本程序适用与STM32F103C8
*******************************************************************************/ 


#include "stm32f10x.h"
#include "Delay.h"

#include "Lcd_Driver.h"
#include "GUI.h"

#include "QDTFT_demo.h"

int main(void)
{

 
  
    Lcd_Init();

    Lcd_Clear(WHITE);

    //Lcd_Clear(BLACK);
    Gui_DrawFont_char(8,20,'a',Purple);
    LCD_ShowNum(8,40,1234,4,RED);
  while(1)
  {  
      

  }
}




