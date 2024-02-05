#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "WS2812B.h"
int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	
	/*OLED显示*/
	OLED_ShowChar(1, 1, 'A');				//1行1列显示字符A
	
	OLED_ShowString(1, 3, "HelloWorld!");	//1行3列显示字符串HelloWorld!
	
	Color_TypeDef temp;
	
	WS2812B_Init();	


	while(1)
	{

          WS2812B_Test();
		
	}	

}
