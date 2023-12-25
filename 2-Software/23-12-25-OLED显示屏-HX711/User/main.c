#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "HX711.h"
int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	
	
	OLED_ShowString(1, 3, "HX711!");	//1行3列显示字符串HelloWorld!
	
	Init_HX711pin();
	Get_Maopi();				//称毛皮重量
	Delay_ms(1000);
	Delay_ms(1000);
	Get_Maopi();				//重新获取毛皮重量
	
	while (1)
	{
        
        
        
        
        Get_Weight();

        
        OLED_ShowNum(2, 1, Weight_Shiwu-46, 5);
     

		
	}
}
