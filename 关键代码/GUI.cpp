#include "GUI.hpp"
#include "FreeRTOS.h"
#include "task.h" 
#include "oled.h"
#include "ps2.hpp"
#include "adc.h"
#include "u8g2.h"
#include "bmp.h" 

void GPIO_Oled_Init();
u8g2_t u8g2;
struct Menu_t Menu;
static u16 Listx_cntt; 
struct SetPoint_t SetPoint;
float Menu_Steps=0;
char MenuFont[][8] = {"Set", "Start", "Music"};

void Start_Move()
{
	int grow;
	for(grow=0;grow<=60	;grow=grow+3)
	{
			u8g2_ClearBuffer(&u8g2);
			u8g2_DrawBox(&u8g2,64-grow,46,grow*2,3);
			u8g2_SendBuffer(&u8g2);
			vTaskDelay(10);
	}
	for(grow=55;grow>=40	;grow=grow-1)
	{
			u8g2_ClearBuffer(&u8g2);
			//显示
			u8g2_SetDrawColor(&u8g2,1);
			u8g2_SetFont(&u8g2,u8g2_font_timR18_tf);
			u8g2_DrawStr(&u8g2,20,grow,"DF CAR");
			//遮盖
			u8g2_SetDrawColor(&u8g2,0);
			u8g2_DrawBox(&u8g2,4,40,128,20);
			//显示横线
			u8g2_SetDrawColor(&u8g2,1);
			u8g2_DrawBox(&u8g2,4,46,120,3);
			u8g2_SendBuffer(&u8g2);
			vTaskDelay(20);
	}
}
void GUI_Task(void *param)
{
	GPIO_Oled_Init();
	TickType_t lastTick = xTaskGetTickCount();
	TickType_t period = 100 / portTICK_RATE_MS; //1ms
	u8g2_Setup_ssd1306_128x64_noname_f(&u8g2,U8G2_R0,u8x8_byte_4wire_sw_spi,u8x8_gpio_and_delay_template);	
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2,0);
	u8g2_ClearBuffer(&u8g2);
	GUI_Menu_Set(-100);
	GUI_Menu_Set(0);
	Start_Move();
	vTaskDelay(1000);		
	while(1)
	{		
		if(RC_Key_==Key_Right)
		{
				static u8 i=0;i++;
				if(i>=5){i=0;
				Menu_Steps=Menu_Steps+1;
				if(Menu_Steps<=-1)
				Menu_Steps=-1;
				GUI_Menu_Set(Menu_Steps);
				}
		}
		if(RC_Key_==Key_Left)
		{	
				static u8 i=0;i++;
				if(i>=5){i=0;
				Menu_Steps=Menu_Steps-1;
				if(Menu_Steps>=1)
				Menu_Steps=1;
				GUI_Menu_Set(Menu_Steps);
			}
		
		}
		if(RC_Key_==Key_Up&&Menu_Steps==-1)
		{	
				static u8 i=0;i++;
				if(i>=5){i=0;
				Menu_Steps=-11;
				if(Menu_Steps>=1)
				Menu_Steps=1;
				GUI_Menu_Set(Menu_Steps);
				SetPoint.Out_len=0;//清空白色底块的长度
				SetPoint.Out_Lisx=-70;SetPoint.LisTarget_x=2;
				SetPoint.Out_Lisx2=-70;SetPoint.LisTarget_x2=-70;
				SetPoint.Out_Lisx3=-70;SetPoint.LisTarget_x3=-70;
				Listx_cntt=0;
			}
		}
		if(RC_Key_==Key_Dwon)
		{	
				static u8 i=0;i++;
				if(i>=5){i=0;
				GUI_Menu_Set(0);
				Menu_Steps=0;
			}
		}
		//动画引擎函数
		DF_Guifx();
		//主菜单
		if(Menu_Steps<=10&&Menu_Steps>=-10)
		{			u8g2_ClearBuffer(&u8g2);
					u8g2_SetFont(&u8g2,u8g2_font_sticker100complete_tr);
					u8g2_DrawXBMP(&u8g2,Menu.Icon_0.Out_x-22 ,Menu.Icon_0.Out_y-22 ,44,44,wheel_Icon);
					u8g2_DrawXBMP(&u8g2,Menu.Icon_L1.Out_x-22,Menu.Icon_L1.Out_y-22,44,44,Set_Icon);
					u8g2_DrawXBMP(&u8g2,Menu.Icon_R1.Out_x-22,Menu.Icon_R1.Out_y-22,44,44,music_Icon);
					static u8 cnnt=0;
					if(Menu_Steps==1)
						{
							cnnt++;if(cnnt>=100)
							{	cnnt=101;
								Menu.Icon_0.Targrt_x=-40;
								Sky_Animation_show(&u8g2);
							}
						}
					if(Menu_Steps!=1)cnnt=0;
					if(Menu_Steps==0)
					u8g2_DrawStr(&u8g2,Menu.Font_0.Out_x    ,Menu.Font_0.Out_y,MenuFont[1]);
					else if(Menu_Steps==-1)
					u8g2_DrawStr(&u8g2,Menu.Font_L1.Out_x   ,Menu.Font_L1.Out_y,MenuFont[0]);
					else if(Menu_Steps==1)
					u8g2_DrawStr(&u8g2,Menu.Font_R1.Out_x   ,Menu.Font_R1.Out_y,MenuFont[2]);
					u8g2_SendBuffer(&u8g2);
		}
		//设置菜单
    if(Menu_Steps==-11)
		{		
			static u8 key_point=0;
			if(Directions_Key_== Key_Up)
				{
					static u8 i=0;i++;if(i>=5){i=0;
					if(key_point>=1)	key_point=key_point-1;if(key_point<=0)key_point=0;}
				}
			if(Directions_Key_== Key_Dwon)
				{
					static u8 i=0;i++;if(i>=5){i=0;
					key_point=key_point+1;if(key_point>=5)key_point=5;}
				}	
				if(Listx_cntt<83) Listx_cntt++;
				if(Listx_cntt>5)
				{
					SetPoint.LisTarget_x2=2;
				}
				if(Listx_cntt>10)
				{
					SetPoint.LisTarget_x3=2;
				}
				
					u8g2_ClearBuffer(&u8g2);
					u8g2_DrawXBMP(&u8g2,Menu.Icon_L1.Out_x-22,Menu.Icon_L1.Out_y-22,44,44,Set_Icon);
					u8g2_DrawXBMP(&u8g2,Menu.Icon_0.Out_x-22 ,Menu.Icon_0.Out_y-22 ,44,44,wheel_Icon);
					//字体显示
					Menu_Set(&u8g2,key_point);
					u8g2_SendBuffer(&u8g2);
		}
		vTaskDelay(10);				
	}
}




void GPIO_Oled_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_0
                          |GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE2 PE3 PE4 PE0
                           PE1 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_0
                          |GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}