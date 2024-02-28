#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "Servo.h"
#include "Key.h"

uint16_t ADValue;			//定义AD值变量
float Voltage;				//定义电压变量


uint8_t KeyNum;			//定义用于接收键码的变量
float Angle;			//定义角度变量

int main(void)
{
	/*模块初始化*/
	OLED_Init();			//OLED初始化
	AD_Init();				//AD初始化
    Servo_Init();		//舵机初始化
	Key_Init();			//按键初始化
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "ADValue:");
	OLED_ShowString(2, 1, "Volatge:0.00V");
    OLED_ShowString(3, 1, "Angle:");	//1行1列显示字符串Angle:
	while (1)
	{
		ADValue = AD_GetValue();					//获取AD转换的值
		Voltage = (float)ADValue / 4095 * 3.3;		//将AD值线性变换到0~3.3的范围，表示电压
		
		OLED_ShowNum(1, 9, ADValue, 4);				//显示AD值
		OLED_ShowNum(2, 9, Voltage, 1);				//显示电压值的整数部分
		OLED_ShowNum(2, 11, (uint16_t)(Voltage * 100) % 100, 2);	//显示电压值的小数部分
		
		Delay_ms(100);			//延时100ms，手动增加一些转换的间隔时间
        
//        KeyNum = Key_GetNum();			//获取按键键码
        Servo_SetAngle(90);			//设置舵机的角度为角度变量
//		if (KeyNum == 1)				//按键1按下
//		{
//			Angle += 30;				//角度变量自增30
//			if (Angle > 180)			//角度变量超过180后
//			{
//				Angle = 0;				//角度变量归零
//			}
//		}
//		Servo_SetAngle(Angle);			//设置舵机的角度为角度变量
//		OLED_ShowNum(3, 7, Angle, 3);	//OLED显示角度变量
        
        
	}
}
