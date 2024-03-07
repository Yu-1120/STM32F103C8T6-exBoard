
//////////////////////////////////////////////////////////////////////////////////	 

/********************************** (C) COPYRIGHT ******************************* 


* File Name : Main.c 
* Author : B站:小昱君__ 
* Version : V1.0 
* Date : 2024年2月19日
* Description : 演示ST7735 硬件SPI驱动 
//本程序适用与STM32F103C8

//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PA5（SCL）
//              SDA   接PA7（SDA）
//              RES   接PB0
//              DC    接PB1
//              CS    接PA4//可以直接接地
//              BLK    接PB10 BLK可以悬空不接；在需要关闭背光的时候将BLK置低电平
*******************************************************************************/ 


#include "stm32f10x.h"
#include "Delay.h"
#include "QDTFT_demo.h"
#include "Lcd_Driver.h"
#include "GUI.h"

int main(void)
{

    SystemInit();	//System init.
    Lcd_Init();
    
    Lcd_Clear(BLACK);
    

    //Gui_DrawFont_num(16,70, "全程技术支持");
    Gui_DrawFont_char(8,20,'a');
  while(1)
  {  
      
    //LCD_ShowNumTES();
    Color_Test();
    // Redraw_Mainmenu();
   // QDTFT_Test_Demo();	//See the test details in QDTFT_Demo.c		
  }
}




