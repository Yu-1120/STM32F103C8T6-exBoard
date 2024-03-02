#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#define DelayTime  50
uint8_t KeyNum;			//定义用于接收键码的变量
float Angle;			//定义角度变量

int main(void)
{
    
    //2023年12月17日21点24分 舵机有问题转不了
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Servo_Init();		//舵机初始化
	Key_Init();			//按键初始化
	
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Angle:");	//1行1列显示字符串Angle:
	while (1)
	{
		Servo_SetAngle(Angle);			//设置舵机的角度为角度变量
        Angle+=10;
		OLED_ShowNum(1, 7, Angle, 3);	//OLED显示角度变量
        Delay_ms(DelayTime);
        if(Angle>=180)
            Angle =0;
	}
}
