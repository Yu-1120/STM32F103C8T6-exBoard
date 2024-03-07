
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  生成日期   : 2018-1111
//  最近修改   : 
//  功能描述   : 0.96寸ISP LCD 4接口演示例程(STM32系列)
/******************************************************************************
//本程序适用与STM32F103C8
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PA5（SCL）
//              SDA   接PA7（SDA）
//              RES   接PB0
//              DC    接PB1
//              CS    接PA4//可以直接接地
//              BLK    接P10 BLK可以悬空不接；在需要关闭背光的时候将BLK置低电平
*******************************************************************************/
// 修改历史   :
// 日    期   : 
// 修改内容   : 
//******************************************************************************/
#ifndef __LCD_DRIVE_H
#define __LCD_DRIVE_H 




#define RED  	0x001f
#define GREEN	0x07e0
#define BLUE 	0xf800
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111
#define Purple 0xF0F8   

#define LCD_CTRLB   	  	GPIOB		//定义TFT数据端口



#define LCD_SCL        	GPIO_Pin_3	
#define LCD_SDA        	GPIO_Pin_4	
#define LCD_RST     	GPIO_Pin_5	
#define LCD_RS         	GPIO_Pin_6
#define LCD_CS     	    GPIO_Pin_7	
#define LCD_BL       	GPIO_Pin_8  



//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)
 /* 液晶控制口置0操作语句宏定义 */
#define	LCD_SCL_SET  	LCD_CTRLB->BSRR=LCD_SCL    
#define	LCD_SDA_SET  	LCD_CTRLB->BSRR=LCD_SDA   

    
#define	LCD_CS_SET  	LCD_CTRLB->BSRR=LCD_CS   
#define	LCD_RS_SET  	LCD_CTRLB->BSRR=LCD_RS 
#define	LCD_BL_SET  	LCD_CTRLB->BSRR=LCD_BL 
#define	LCD_RST_SET  	LCD_CTRLB->BSRR=LCD_RST 

 /* 液晶控制口置0操作语句宏定义 */

#define	LCD_SCL_CLR  	LCD_CTRLB->BRR=LCD_SCL  
#define	LCD_SDA_CLR  	LCD_CTRLB->BRR=LCD_SDA 
#define	LCD_CS_CLR  	LCD_CTRLB->BRR=LCD_CS 
    
#define	LCD_RST_CLR  	LCD_CTRLB->BRR=LCD_RST
#define	LCD_RS_CLR  	LCD_CTRLB->BRR=LCD_RS 
#define	LCD_BL_CLR  	LCD_CTRLB->BRR=LCD_BL 

 /* 数据输出 */
#define LCD_DATAOUT(x) LCD_DATA->ODR=x; 
 /* 数据输入 */
#define LCD_DATAIN     LCD_DATA->IDR;   


// 这个宏定义的作用是将给定的数据data写入LCD，并按照一定的时序控制信号进行操作。
#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



void LCD_GPIO_Init(void);
void Lcd_WriteIndex(u8 Index);
void Lcd_WriteData(u8 Data);
void Lcd_WriteReg(u8 Index,u8 Data);
u16 Lcd_ReadReg(u8 LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(u16 Color);
void Lcd_SetXY(u16 x,u16 y);
void Gui_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int Lcd_ReadPoint(u16 x,u16 y);
void Lcd_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_WriteData_16Bit(u16 Data);

//寄存器说明
#define	Sleep_Exit 		0x11
#define	Sleep_In			0x10
 /* 不翻转颜色 */
#define	No_FlipColor 		0x21  
 /* 翻转颜色 */
#define	FlipColor			0x20 
/* 帧速率控制（正常模式/全色） */
#define	FrameRateControl 			0xB1  //

/* 控制屏幕翻转的  分别是C0/AO/00/60,对应着每次90度的翻转 */
#define	ControlScreenFlip			0x36  //
#define	PowerControl_1			0xC0  // 
#define	PowerControl_2			0xC1  
#define	PowerControl_3			0xC2  
#define	PowerControl_4			0xC3  
#define	PowerControl_5			0xC4  


#endif

