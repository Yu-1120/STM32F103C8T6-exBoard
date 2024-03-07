#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "TFT-7P.h"


/********************************** (C) COPYRIGHT ******************************* 
* Author : Bilibili:С�ž�__ 
* Version : V1.0 
ʵ��˵����
    
* GMT024-03-S ģ�� 2.4��   7PIN ���� TFT FOR STM32F103
* 240*320   16/18BIT���
* STM32F103����

* PB5----3  SCK /SCL
* PB6----4  SDA
* PB7---5  RST/RESET
* PB8    ---6   DC /A0
* PB9 ----7   /WR /CS
* VCC(3.3V) ---- BL
* 
* BY:GU 
* ST7789 ����������ģ����ô���ת������8bit����ģʽ

* Ĭ�����ݸ�ʽλRGB565      ,
        ,    
*******************************************************************************/ 


const unsigned char  *point;
void main(void)
{ 
	point= &picture_tab[0];

    
	IO_init();
	SPI_SCK_0;
	SPI_RST_0;
	//Delay_ms(1000);
	SPI_RST_1;
	//Delay_ms(1000);
	TFT_init();
    display_char16_16(20,280,BLUE,0);
	//display_char16_16(36,280,GREEN,1);
	//display_char16_16(60,280,RED,2);
        
	while(1)
	{
		Picture_Display(point);


	}
}