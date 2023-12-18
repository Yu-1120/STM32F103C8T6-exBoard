#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"

#include "dht11.h"

#include "usart1.h"
#include "usart2.h"

uint8_t i=0,j=0;

uint8_t temp,humi,tempL;
//2023��12��18��10��20�����гɹ�--
u8 temp,humi;

int main(void)
{
    DHT11_Init();    //PA11
    Usart1_Init(115200);     //����1���ܳ�ʼ��
    Usart2_Init(115200);   //����2���ܳ�ʼ��

    while(1)
    {  
        DHT11_Read_Data(&temp,&humi,&tempL);
        u1_printf("temp:%d  humi:%d\r \n",temp,humi);
    }
}
