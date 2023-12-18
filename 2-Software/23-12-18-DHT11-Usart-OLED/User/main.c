#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"

#include "dht11.h"

#include "usart1.h"
#include "usart2.h"
#include "OLED.h"
uint8_t i=0,j=0;

uint8_t temp,humi,tempL;
//2023��12��18��10��20�����гɹ�--
u8 temp,humi;

int main(void)
{
    DHT11_Init();    //PA11
    Usart1_Init(115200);     //����1���ܳ�ʼ��
    Usart2_Init(115200);   //����2���ܳ�ʼ��
    OLED_Init();		//OLED��ʼ��
    	/*OLED��ʾ*/
	OLED_ShowString(1, 1, "HelloWorld!");	//1��3����ʾ�ַ���HelloWorld!
	

    

    while(1)
    {  
        DHT11_Read_Data(&temp,&humi,&tempL);
        u1_printf("temp:%d  humi:%d\r \n",temp,humi);
        
        if (DHT11_Read_Data(&temp,&humi,&tempL) == 0)
        {
            
        
            
            OLED_ShowString(2, 1, "Temp:");
            OLED_ShowNum(2,6, temp, 2);

            
            OLED_ShowString(3, 1, "Humi:");
            OLED_ShowNum(3,6, humi, 2);
       
            
          
            
        }
        else
        {
            OLED_ShowString(0, 0, "read faile");
        }
        
        
    }
}
