
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��������   : 2018-1111
//  ����޸�   : 
//  ��������   : 0.96��ISP LCD 4�ӿ���ʾ����(STM32ϵ��)
/******************************************************************************
//������������STM32F103C8
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��
//              RES   ��PB0
//              DC    ��PB1
//              CS    ��PA4//����ֱ�ӽӵ�
//              BLK    ��PB10 BLK�������ղ��ӣ�����Ҫ�رձ����ʱ��BLK�õ͵�ƽ
*******************************************************************************/
// �޸���ʷ   :
// ��    ��   : 
// �޸�����   : 
//******************************************************************************/
#include "stm32f10x.h"
#include "delay.h"
#include "QDTFT_demo.h"
#include "Lcd_Driver.h"
#include "GUI.h"


int main(void)
{
    u8 t;
    t=0;
    SystemInit();	//System init.
    delay_init(72);//Delay init.
    Lcd_Init();

    //Lcd_Clear(WHITE);

    Lcd_Clear(BLACK);
    Gui_DrawFont_char(8,20,'a');
    LCD_ShowNum(8,40,1234,4);
    // while(t<255)
    // {  

    //		t++;
    //		LCD_ShowNum(50,100,t,3);
    //		if(t==255) t=0;
    // }
  while(1)
  {  
      
    // showimage(gImage_qq);
    // Color_Test();
    //Redraw_Mainmenu();
    //QDTFT_Test_Demo();	//See the test details in QDTFT_Demo.c		
  }
}


