#include "oled.h"
#include "flash.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "GUI.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "ps2.hpp"
#include "DF_User_Config.hpp"
#include "adc.h"

typedef struct START
{
    uint16_t x;
    uint16_t y;
    uint16_t speed;
    uint8_t speedcount;
    uint8_t isexist;
} Star;
Star star[128] = {0}
/// @brief 转字符串
char* Int2String(float num,char *str)
{
    sprintf(str, "%.2f", num);
    return str;
}
ui_List_t Menu_Set_list[]={

	{"Type" ,4*11},//轮子类型
	{"Reduct",6*11-3},//减速比
	{"WheDiam" ,7*11-2},	//轮子直径
	{"Econ" ,4*11},	//编码器
	{"RoatPol" ,7*11-3},//轮子编码器极性
	{"MotPol" ,6*11},//电机极性
};
extern struct Menu_t Menu;
extern struct SetPoint_t SetPoint;
void Font_Rset()
{				//Font
			Menu.Font_0.Targrt_x=40;Menu.Font_0.Out_x=40;
			Menu.Font_0.Targrt_y=100;Menu.Font_0.Out_y=100;
			
			Menu.Font_R1.Targrt_x=40;Menu.Font_R1.Out_x=40;
			Menu.Font_R1.Targrt_y=100;Menu.Font_R1.Out_y=100;
			
			Menu.Font_L1.Targrt_x=50;Menu.Font_L1.Out_x=50;
			Menu.Font_L1.Targrt_y=100;Menu.Font_L1.Out_y=100;
}
void Menu_Set(u8g2_t *u8g2 ,int Key_point)
{		
		static u8 cnnt=0;
		u8g2_SetFont(u8g2,u8g2_font_courB12_tr);
		u8g2_SetFontMode(u8g2,1);
		//高亮光标
		u8g2_SetDrawColor(u8g2,1);
	  SetPoint.Targrt_y=Key_point*17;
		if(Key_point>=2)
		SetPoint.Targrt_y=2*17;	
		SetPoint.Targrt_len=Menu_Set_list[Key_point].len;
		u8g2_DrawRBox(u8g2,0,SetPoint.Out_y,SetPoint.Out_len,16,4);
		//汉字
		u8g2_SetDrawColor(u8g2,2);
		if(Key_point>=2)
		{SetPoint.LisTarget_y=(Key_point-2)*17;}
		u8g2_DrawStr(u8g2,SetPoint.Out_Lisx2,12   -SetPoint.Out_Lisy,Menu_Set_list[0].str);
		u8g2_DrawStr(u8g2,SetPoint.Out_Lisx,24+5 -SetPoint.Out_Lisy,Menu_Set_list[1].str);
		u8g2_DrawStr(u8g2,SetPoint.Out_Lisx2 ,36+10-SetPoint.Out_Lisy,Menu_Set_list[2].str);
		u8g2_DrawStr(u8g2,SetPoint.Out_Lisx3,48+15-SetPoint.Out_Lisy,Menu_Set_list[3].str);
		u8g2_DrawStr(u8g2,SetPoint.Out_Lisx2,60+20-SetPoint.Out_Lisy,Menu_Set_list[4].str);
		u8g2_DrawStr(u8g2,SetPoint.Out_Lisx,72+25-SetPoint.Out_Lisy,Menu_Set_list[5].str);	
}
//菜单界面生成中心点
void GUI_Menu_Set(int flag)
{
	int x_base=64;int y_base=22;
	if(flag==-100)
		{
			Menu.Icon_L1.Targrt_x=0;Menu.Icon_L1.Out_x=0;
			Menu.Icon_L1.Targrt_y=90;Menu.Icon_L1.Out_y=90;
			
			Menu.Icon_0.Targrt_x=64;Menu.Icon_0.Out_x=64;
			Menu.Icon_0.Targrt_y=90;Menu.Icon_0.Out_y=90;
			
			Menu.Icon_R1.Targrt_x=128;Menu.Icon_R1.Out_x=128;
			Menu.Icon_R1.Targrt_y=90; Menu.Icon_R1.Out_y=90;
			Font_Rset();
		}
	if(flag==0)
		{
			Menu.Icon_0.Targrt_x=x_base;
			Menu.Icon_0.Targrt_y=y_base;
					
			Menu.Icon_L1.Targrt_x=x_base-BetUiDis;
			Menu.Icon_L1.Targrt_y=y_base;
			
			Menu.Icon_R1.Targrt_x=x_base+BetUiDis;
			Menu.Icon_R1.Targrt_y=y_base;
			//Font
			Font_Rset();
			Menu.Font_0.Targrt_y=64;
			
		}
	if(flag==-1)
		{
			Menu.Icon_0.Targrt_x=x_base 					+BetUiDis;
			Menu.Icon_0.Targrt_y=y_base;
			
			Menu.Icon_L1.Targrt_x=x_base-BetUiDis +BetUiDis;
			Menu.Icon_L1.Targrt_y=y_base;
			
			Menu.Icon_R1.Targrt_x=x_base+BetUiDis +BetUiDis;
			Menu.Icon_R1.Targrt_y=y_base;
			//Font
			Font_Rset();
			Menu.Font_L1.Targrt_y=64;
		}	
	if(flag==1)
		{
			Menu.Icon_0.Targrt_x=x_base 					-BetUiDis;
			Menu.Icon_0.Targrt_y=y_base;
			
			Menu.Icon_L1.Targrt_x=x_base-BetUiDis-BetUiDis;
			Menu.Icon_L1.Targrt_y=y_base;
			
			Menu.Icon_R1.Targrt_x=x_base+BetUiDis-BetUiDis;
			Menu.Icon_R1.Targrt_y=y_base;
				//Font
			Font_Rset();
			Menu.Font_R1.Targrt_y=64;
		}	
		if(flag==-11)
		{
			Menu.Icon_0.Targrt_x=x_base 					+2*BetUiDis-10;
			Menu.Icon_0.Targrt_y=y_base;
			
			Menu.Icon_L1.Targrt_x=x_base-BetUiDis +2*BetUiDis-10;
			Menu.Icon_L1.Targrt_y=y_base;
			
			Menu.Icon_R1.Targrt_x=x_base+BetUiDis +2*BetUiDis-10;
			Menu.Icon_R1.Targrt_y=y_base;
			//Font
			Font_Rset();
			Menu.Font_0.Targrt_y=64;
		}	
};
void DF_Guifx()
{
	float a = 0.80f;
	//menu 0
	Menu.Icon_0.Out_x =(a)*Menu.Icon_0.Out_x+(1-a)*Menu.Icon_0.Targrt_x;
	Menu.Icon_0.Out_y =(a)*Menu.Icon_0.Out_y+(1-a)*Menu.Icon_0.Targrt_y;
	//menu L1
	Menu.Icon_L1.Out_x =(a)*Menu.Icon_L1.Out_x+(1-a)*Menu.Icon_L1.Targrt_x;
	Menu.Icon_L1.Out_y =(a)*Menu.Icon_L1.Out_y+(1-a)*Menu.Icon_L1.Targrt_y;
	//menu R1
	Menu.Icon_R1.Out_x =(a)*Menu.Icon_R1.Out_x+(1-a)*Menu.Icon_R1.Targrt_x;
	Menu.Icon_R1.Out_y =(a)*Menu.Icon_R1.Out_y+(1-a)*Menu.Icon_R1.Targrt_y;
	//menu 0 
	Menu.Font_0.Out_y =(a)*Menu.Font_0.Out_y+(1-a)*Menu.Font_0.Targrt_y;
	Menu.Font_L1.Out_y =(a)*Menu.Font_L1.Out_y+(1-a)*Menu.Font_L1.Targrt_y;
	Menu.Font_R1.Out_y =(a)*Menu.Font_R1.Out_y+(1-a)*Menu.Font_R1.Targrt_y;
	//set_point
	SetPoint.Out_x=(a)*SetPoint.Out_x+(1-a)*SetPoint.Targrt_x;
	SetPoint.Out_y=(a)*SetPoint.Out_y+(1-a)*SetPoint.Targrt_y;
	SetPoint.Out_len=(a)*SetPoint.Out_len+(1-a)*SetPoint.Targrt_len;
	//set_lis
	SetPoint.Out_Lisy=(a)*SetPoint.Out_Lisy+(1-a)*SetPoint.LisTarget_y;
	SetPoint.Out_Lisx=(a)*SetPoint.Out_Lisx+(1-a)*SetPoint.LisTarget_x;
	SetPoint.Out_Lisx2=(a)*SetPoint.Out_Lisx2+(1-a)*SetPoint.LisTarget_x2;
	SetPoint.Out_Lisx3=(a)*SetPoint.Out_Lisx3+(1-a)*SetPoint.LisTarget_x3;
}

uint8_t u8x8_gpio_and_delay_template(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
      break;														// can be used to setup pins
    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
		
      break;    
    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
		  __NOP();
      break;
    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
		for (size_t  n = 0; n < 300; n++)//(size_t  n = 0; n < 640; n++)
		{
		   __NOP();
		}
      break;
    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
		vTaskDelay(arg_int*0.5f);
      break;
    case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
		arg_int?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_RESET);
      break;
    case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
		arg_int?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
      break;
    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
		arg_int?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_RESET);
      break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
		arg_int?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_RESET);
      break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
		arg_int?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_RESET);
      break;
  }
  return 1;
}










