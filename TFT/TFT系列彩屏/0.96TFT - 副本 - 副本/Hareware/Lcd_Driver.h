
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
//              BLK    ��P10 BLK�������ղ��ӣ�����Ҫ�رձ����ʱ��BLK�õ͵�ƽ
*******************************************************************************/
// �޸���ʷ   :
// ��    ��   : 
// �޸�����   : 
//******************************************************************************/
#ifndef __LCD_DRIVE_H
#define __LCD_DRIVE_H 




#define RED  	0x001f
#define GREEN	0x07e0
#define BLUE 	0xf800
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111
#define Purple 0xF0F8   

#define LCD_CTRLB   	  	GPIOB		//����TFT���ݶ˿�



#define LCD_SCL        	GPIO_Pin_3	
#define LCD_SDA        	GPIO_Pin_4	
#define LCD_RST     	GPIO_Pin_5	
#define LCD_RS         	GPIO_Pin_6
#define LCD_CS     	    GPIO_Pin_7	
#define LCD_BL       	GPIO_Pin_8  



//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)
 /* Һ�����ƿ���0�������궨�� */
#define	LCD_SCL_SET  	LCD_CTRLB->BSRR=LCD_SCL    
#define	LCD_SDA_SET  	LCD_CTRLB->BSRR=LCD_SDA   

    
#define	LCD_CS_SET  	LCD_CTRLB->BSRR=LCD_CS   
#define	LCD_RS_SET  	LCD_CTRLB->BSRR=LCD_RS 
#define	LCD_BL_SET  	LCD_CTRLB->BSRR=LCD_BL 
#define	LCD_RST_SET  	LCD_CTRLB->BSRR=LCD_RST 

 /* Һ�����ƿ���0�������궨�� */

#define	LCD_SCL_CLR  	LCD_CTRLB->BRR=LCD_SCL  
#define	LCD_SDA_CLR  	LCD_CTRLB->BRR=LCD_SDA 
#define	LCD_CS_CLR  	LCD_CTRLB->BRR=LCD_CS 
    
#define	LCD_RST_CLR  	LCD_CTRLB->BRR=LCD_RST
#define	LCD_RS_CLR  	LCD_CTRLB->BRR=LCD_RS 
#define	LCD_BL_CLR  	LCD_CTRLB->BRR=LCD_BL 

 /* ������� */
#define LCD_DATAOUT(x) LCD_DATA->ODR=x; 
 /* �������� */
#define LCD_DATAIN     LCD_DATA->IDR;   


// ����궨��������ǽ�����������dataд��LCD��������һ����ʱ������źŽ��в�����
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

//�Ĵ���˵��
#define	Sleep_Exit 		0x11
#define	Sleep_In			0x10
 /* ����ת��ɫ */
#define	No_FlipColor 		0x21  
 /* ��ת��ɫ */
#define	FlipColor			0x20 
/* ֡���ʿ��ƣ�����ģʽ/ȫɫ�� */
#define	FrameRateControl 			0xB1  //

/* ������Ļ��ת��  �ֱ���C0/AO/00/60,��Ӧ��ÿ��90�ȵķ�ת */
#define	ControlScreenFlip			0x36  //
#define	PowerControl_1			0xC0  // 
#define	PowerControl_2			0xC1  
#define	PowerControl_3			0xC2  
#define	PowerControl_4			0xC3  
#define	PowerControl_5			0xC4  


#endif

