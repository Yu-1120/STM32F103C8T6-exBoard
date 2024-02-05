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
    WS2812B_Test();
    temp.R = 0xff;
	temp.G = 0x00;
	temp.B = 0x00; //0xff
	WS2812B_FillColor(10,20,&temp);
	while(1)
	{
		Delay_ms(50); 
        if(temp.R == 0xff){
            OLED_ShowString(2, 3, "RED!");	
        }else if(temp.G == 0xff){
            OLED_ShowString(2, 3, "Green!");	
        }else if(temp.B == 0xff){
            OLED_ShowString(2, 3, "Blue!");	
        }else if(temp.B == 0xff){
            OLED_ShowString(2, 3, "purple!");	
        }
        
        
        WS2812B_MovePixel(2);
        WS2812B_RefreshPixel();
		
	}	


}
