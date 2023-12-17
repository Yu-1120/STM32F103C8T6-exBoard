#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
    //2023年12月17日20点38分运行成功
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	while (1)
	{
//		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
//		Delay_ms(200);
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
//		Delay_ms(800);
//		
//		GPIO_WriteBit(GPIOB, GPIO_Pin_11, Bit_RESET);
//		Delay_ms(500);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_11, Bit_SET);
//		Delay_ms(500);
//		
//		GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)0);
//		Delay_ms(500);
//		GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)1);
//		Delay_ms(500);
	}
}
