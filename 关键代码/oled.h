#ifndef __OLED_H
#define __OLED_H
#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32f4xx_hal.h"
#include "u8g2.h" 
#include "bmp.h" 
#include "main.h"
#include <stdio.h>
#include "usart.h"
  						 
//==============OLED��������=================
#define OLED_RST_GPIO			GPIOE
#define OLED_RST_GPIO_PIN		GPIO_PIN_2
#define OLED_DC_GPIO				GPIOE
#define OLED_DC_GPIO_PIN			GPIO_PIN_1
#define OLED_SCLK_GPIO			GPIOE
#define OLED_SCLK_GPIO_PIN		GPIO_PIN_4
#define OLED_SDIN_GPIO			GPIOE
#define OLED_SDIN_GPIO_PIN		GPIO_PIN_3


//CS
#define OLED_CS_Clr()  //NOT USE
#define OLED_CS_Set()  //NOT USE

//RES
#define OLED_RST_Clr() HAL_GPIO_WritePin(OLED_RST_GPIO, OLED_RST_GPIO_PIN, GPIO_PIN_RESET)	//RES RES => ��RES��RST������
#define OLED_RST_Set() HAL_GPIO_WritePin(OLED_RST_GPIO, OLED_RST_GPIO_PIN, GPIO_PIN_SET)

//DC
#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DC_GPIO, OLED_DC_GPIO_PIN, GPIO_PIN_RESET)
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DC_GPIO, OLED_DC_GPIO_PIN, GPIO_PIN_SET)

//SCLK,D0
#define OLED_SCLK_Clr() HAL_GPIO_WritePin(OLED_SCLK_GPIO, OLED_SCLK_GPIO_PIN, GPIO_PIN_RESET)
#define OLED_SCLK_Set() HAL_GPIO_WritePin(OLED_SCLK_GPIO, OLED_SCLK_GPIO_PIN, GPIO_PIN_SET)

//SDIN,D1
#define OLED_SDIN_Clr() HAL_GPIO_WritePin(OLED_SDIN_GPIO, OLED_SDIN_GPIO_PIN, GPIO_PIN_RESET)
#define OLED_SDIN_Set() HAL_GPIO_WritePin(OLED_SDIN_GPIO, OLED_SDIN_GPIO_PIN, GPIO_PIN_SET)

 		     
#define OLED_CMD  0	//дָ��
#define OLED_DATA 1	//д����


uint8_t u8x8_gpio_and_delay_template(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void DF_Guifx();
void Sky_Animation_show(u8g2_t *u8g2 );
void GUI_Menu_Set(int flag);//10 64 118
void Menu_Set(u8g2_t *u8g2 ,int flag);
//ui menu list
typedef struct{
	const char *str;
	uint8_t len;
}ui_List_t; 
#ifdef __cplusplus
}
#endif
#endif  
	 




