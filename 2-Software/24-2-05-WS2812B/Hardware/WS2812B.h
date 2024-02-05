/************************************************************
Copyright (C), 2013-2020, XINZHIYIKONG.Co.,Ltd.
@FileName: WS2812B.h
@Author  : ������ QQ:570525287
@Version : 1.0
@Date    : 2020-12-25
@Description: WS2812Bȫ��LED������
@Function List:
@History    : 
<author> <time> <version > <desc>

***********************************************************/

#ifndef __WS2812B_H
#define	__WS2812B_H

#include "stm32f10x.h"     

//WS2812B IO ����  ע���ʼ��APBʱ��ҲҪ�޸�
#define WS2812B_PORT		GPIOC
#define WS2812B_PIN			GPIO_Pin_15
#define WS2812B_RCC_AHB		RCC_APB2Periph_GPIOC  //RCCʱ��

#define WS2812B_Hi()		WS2812B_PORT->BSRR=WS2812B_PIN	//GPIO_ResetBits(LED1_PORT, LED1_PIN)
#define WS2812B_Low()		WS2812B_PORT->BRR=WS2812B_PIN	//GPIO_SetBits(LED1_PORT, LED1_PIN)

//��ɫ
typedef struct color{
	u8 G;
	u8 R;
	u8 B;
}Color_TypeDef;

//------------------------
#define PIXEL_NUM	59	//LED�Ƶĸ���

void WS2812B_Init(void);
void WS2812B_Reset(void);
void WS2812B_WriteColor(Color_TypeDef *pColor);
void WS2812B_RefreshPixel(void);

void WS2812B_FillColor(u16 start,u16 end,Color_TypeDef *pColor);
void WS2812B_MovePixel(u8 dir);

void WS2812B_Test(void);
#endif /* __WS2812B_H */


    