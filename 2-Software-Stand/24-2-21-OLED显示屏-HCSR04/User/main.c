#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "HCSR04.h"
/*
1、HC-SR04模块必须使用5V供电，不能是3.3V
2、若单是测距，无需使用中断
3、Echo和Trig两个引脚可以任意接可用的GPIO，和定时器无关
*/
int main(void)
{
    
    int Distance_mm;			//获取距离测量结果，单位毫米（mm）		
	int Distance_m;	//转换为米（m）为单位，将整数部分放入Distance_m
	int Distance_m_p;	//转换为米（m）为单位，将小数部分放入Distance_m_p
	float Distance;
    
	OLED_Init();	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	OLED_ShowChar(1, 1, 'A');				//1行1列显示字符A
	
	OLED_ShowString(1, 3, "HelloWorld!");	//1行3列显示字符串HelloWorld!
    Timer_Init();
	HC_SR04_Init();
	
	while (1)
	{
            Distance_mm=sonar_mm();			//获取距离测量结果，单位毫米（mm）		
			Distance_m=Distance_mm/1000;	//转换为米（m）为单位，将整数部分放入Distance_m
            OLED_ShowNum(2, 1, Distance_mm,8);
        
        
	}
}
