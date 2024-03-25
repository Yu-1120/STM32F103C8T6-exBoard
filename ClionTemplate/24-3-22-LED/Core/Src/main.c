#include "stm32f10x.h"
#include "USART.h"
#include "Delay.h"
#include "string.h"
#include "LED.h"
int TRUE=1;
int main(void)
{
    uart_init(115200);
    LED_Init();
    Delay_init();
    while(TRUE){
        LED1_Turn();

        USART_SEND(USART1,"Hello World!\n");
        Delay_ms(500);
    }
    return 0;
}

