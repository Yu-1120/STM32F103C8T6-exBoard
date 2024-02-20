#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "string.h"


int TRUE=1;
int main(void)
{
    uart_init(115200);
    delay_init();
    while(TRUE){
        USART_SEND(USART1,"Hello World!\n");
        delay_ms(1000);
    }
    return 0;
}
