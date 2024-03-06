#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#define Relay_Pin  GPIO_Pin_8
int main(void)
{
    //2023年12月17日20点38分运行成功
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = Relay_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	while (1)
	{
		GPIO_ResetBits(GPIOB, Relay_Pin);
		Delay_ms(500);
		GPIO_SetBits(GPIOB, Relay_Pin);
		Delay_ms(500);
	
	}
}
