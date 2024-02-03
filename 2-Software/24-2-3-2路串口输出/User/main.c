#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "dht11.h"
#include "usart1.h"
#include "usart2.h"




u8 temp,humi,tempL;

int main(void)
{

	
    DHT11_Init();    //PA11
    OLED_I2C_Init();

    Usart1_Init(9600);     //串口1功能初始化，波特率9600   PA  9 10 
    Usart2_Init(115200);   //串口2功能初始化，波特率115200	 PA 2  3 

	
    while(1)
    {  

        DHT11_Read_Data(&temp,&humi,&tempL);
        //u1_printf("temp:%d  humi:%d\r \n",temp,humi);

        u1_printf("1234\r\n");
        
        
        

    }
}
