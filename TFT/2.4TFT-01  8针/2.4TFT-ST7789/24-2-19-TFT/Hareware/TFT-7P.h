

#ifndef __TFT_H
#define __TFT_H
/********************金逸晨**************************
*****************GMT024-03-S 模块 2.4寸   7PIN 串口 TFT FOR STM32F103*************
***************************240*320   16/18BIT真彩***********************
*****STM32F103驱动**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    PB7---5  RST   ,
      PB8    ---6   DC   ,    PB9 ----7   /WR 
***** BY:GU 
*********ST7789 控制器，本模块采用串口转换并行8bit数据模式
默认数据格式位RGB565
********************************************************/
#include "stm32f10x.h"

#define     RED          0XF800	  //红色
#define     GREEN        0X07E0	  //绿色
#define     BLUE         0X001F	  //蓝色
#define     WHITE        0XFFFF	  //白色

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 320
#define TFT_COLUMN_OFFSET 0

#define PIC_NUM 28800			//图片数据大小


/**********SPI引脚分配，连接TFT屏，更具实际情况修改*********/

#define SPI_SCK_0  GPIOB->BRR=0X0020       // 设置sck接口到PB5   清零
#define SPI_SCK_1  GPIOB->BSRR=0X0020       //置位
#define SPI_SDA_0  GPIOB->BRR=0X0040       // 设置SDA接口到PB6
#define SPI_SDA_1  GPIOB->BSRR=0X0040
#define SPI_RST_0  GPIOB->BRR=0X0080       // 设置RST接口到PB7
#define SPI_RST_1  GPIOB->BSRR=0X0080
#define SPI_DC_0   GPIOB->BRR=0X0100      // 设置DC接口到PB8
#define SPI_DC_1   GPIOB->BSRR=0X0100
#define SPI_WR_0   GPIOB->BRR=0X0200    // 设置/WR 或CS接口到PB9
#define SPI_WR_1   GPIOB->BSRR=0X0200

extern const unsigned char  chines_word[   ][32];   //汉字码
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









  