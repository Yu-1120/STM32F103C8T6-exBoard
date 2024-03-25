#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ADValue;			//定义AD值变量
float Voltage;				//定义电压变量


u8 DigitalConvLight()
{
	u8 i = 0;
	float temp = 0;
	
	while(i<=4)
	{
		temp += AD_GetValue();
		i++;
	}
	temp = 100*(1 - temp/5/4000);
	
	return (u8)temp;
}


int main(void)
{
	/*模块初始化*/
	OLED_Init();			//OLED初始化
	AD_Init();				//AD初始化
	

	
	while (1)
	{
		ADValue = AD_GetValue();					//获取AD转换的值
		Voltage = (float)ADValue / 4095 * 3.3;		//将AD值线性变换到0~3.3的范围，表示电压
		OLED_ShowString(1,1,"LightSize:");
		OLED_ShowNum(1, 11, DigitalConvLight(), 2);				//显示AD值
              
		
		Delay_ms(100);			//延时100ms，手动增加一些转换的间隔时间
	}
}


