#include "../Inc/stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "string.h"


int TRUE=1;

int main(void)
{
	u32 t=0;
	uart_init(115200);
	delay_init(100);

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Configure C13 pin(PC13) in output function */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);


    RCC_ClocksTypeDef clock;
    RCC_GetClocksFreq(&clock);

    while(TRUE){
        char data[80];
        memset(data,0, sizeof(data));
        sprintf(data,"系统频率:%d\n高速总线频率:%d\n",clock.SYSCLK_Frequency,clock.HCLK_Frequency);
        USART_SEND(USART1,data);

        GPIO_ResetBits(GPIOC,GPIO_Pin_13);
        delay_ms(500);
        GPIO_SetBits(GPIOC,GPIO_Pin_13);
        delay_ms(500);
    }
}


