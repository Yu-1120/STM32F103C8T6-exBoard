#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "inv_mpu.h"


float Pitch,Roll,Yaw;

int main(void)
{
	OLED_Init();
	MPU6050_DMP_Init();
	OLED_ShowImage(0,0,128,18,mpu6050);
	OLED_ShowString(28,25,"Pitch:",OLED_6X8);
	OLED_ShowString(28,40,"Roll :",OLED_6X8);
	OLED_ShowString(28,56,"Yaw  :",OLED_6X8);
	while (1)
	{
        MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);
		OLED_ShowSignedNum(65,25,Pitch,4,OLED_6X8);
		OLED_ShowSignedNum(65,40,Roll,4,OLED_6X8);
		OLED_ShowSignedNum(65,56,Yaw,4,OLED_6X8);
		OLED_Update();
	}

}
