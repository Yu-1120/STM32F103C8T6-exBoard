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

//    Usart1_Init(9600);     //����1���ܳ�ʼ����������9600   PA  9 10 
//    Usart2_Init(115200);   //����2���ܳ�ʼ����������115200	 PA 2  3 

	/*OLED��ʾ*/
	OLED_ShowChar(1, 1, 'A');				//1��1����ʾ�ַ�A
	
	OLED_ShowString(1, 3, "HelloWorld!");	//1��3����ʾ�ַ���HelloWorld!
	
    while(1)
    {  

        DHT11_Read_Data(&temp,&humi,&tempL);
        //u1_printf("temp:%d  humi:%d\r \n",temp,humi);
        
        u1_printf("1234\r\n");
        
        u1_printf(temp+"\r\n");
        

    }
}
