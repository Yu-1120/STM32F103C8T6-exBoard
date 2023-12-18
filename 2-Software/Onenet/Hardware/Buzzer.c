#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}
}
void Buzzer_Star(void)
{      
		 
		 Buzzer_ON();
	     Delay_ms(500);
	     Buzzer_OFF();
	     Delay_ms(500);
	     Buzzer_ON();
	     Delay_ms(500);
	     Buzzer_OFF();
	     Delay_ms(500);
	     Buzzer_ON();
	     Delay_ms(500);
	     Buzzer_OFF();
	     Delay_ms(900);
}
