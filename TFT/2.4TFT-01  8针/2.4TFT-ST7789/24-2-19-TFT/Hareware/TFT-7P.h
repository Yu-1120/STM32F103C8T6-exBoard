

#ifndef __TFT_H
#define __TFT_H
/********************���ݳ�**************************
*****************GMT024-03-S ģ�� 2.4��   7PIN ���� TFT FOR STM32F103*************
***************************240*320   16/18BIT���***********************
*****STM32F103����**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    PB7---5  RST   ,
      PB8    ---6   DC   ,    PB9 ----7   /WR 
***** BY:GU 
*********ST7789 ����������ģ����ô���ת������8bit����ģʽ
Ĭ�����ݸ�ʽλRGB565
********************************************************/
#include "stm32f10x.h"

#define     RED          0XF800	  //��ɫ
#define     GREEN        0X07E0	  //��ɫ
#define     BLUE         0X001F	  //��ɫ
#define     WHITE        0XFFFF	  //��ɫ

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 320
#define TFT_COLUMN_OFFSET 0

#define PIC_NUM 28800			//ͼƬ���ݴ�С


/**********SPI���ŷ��䣬����TFT��������ʵ������޸�*********/

#define SPI_SCK_0  GPIOB->BRR=0X0020       // ����sck�ӿڵ�PB5   ����
#define SPI_SCK_1  GPIOB->BSRR=0X0020       //��λ
#define SPI_SDA_0  GPIOB->BRR=0X0040       // ����SDA�ӿڵ�PB6
#define SPI_SDA_1  GPIOB->BSRR=0X0040
#define SPI_RST_0  GPIOB->BRR=0X0080       // ����RST�ӿڵ�PB7
#define SPI_RST_1  GPIOB->BSRR=0X0080
#define SPI_DC_0   GPIOB->BRR=0X0100      // ����DC�ӿڵ�PB8
#define SPI_DC_1   GPIOB->BSRR=0X0100
#define SPI_WR_0   GPIOB->BRR=0X0200    // ����/WR ��CS�ӿڵ�PB9
#define SPI_WR_1   GPIOB->BSRR=0X0200

extern const unsigned char  chines_word[   ][32];   //������
extern const unsigned char  picture_tab[PIC_NUM];


void SYS_init(unsigned char PLL);
void IO_init(void);

void SPI_SendByte(unsigned  char byte);
void TFT_SEND_CMD(unsigned char o_command);
void TFT_SEND_DATA(unsigned  char o_data);
void TFT_clear(void);
void TFT_full(unsigned int color);
void TFT_init(void);
void display_char16_16(unsigned int x,unsigned int y,unsigned long color,unsigned char word_serial_number);
void Picture_Display(const unsigned char *ptr_pic);

#endif









  