#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "DHT11.h"
#include "Relay.h"
 u8 TempH, TempL, HumiH, HumiL;
 //2023年12月1723点54分-运行成功--DHT11缺点读取速度慢
int main(void)
{

	OLED_Init();		
	DHT11_Init();
    Relay_Init();
	OLED_ShowChar(1, 1, 'Y');				//1行1列显示字符A
	OLED_ShowString(1, 3, "HelloWorld!");	//1行3列显示字符串HelloWorld!
	

  
   
   
    while (1)
    {
        if (DHT11_ReadData(&TempH, &TempL, &HumiH, &HumiL) == 1)
        {
            
          if(TempH>=15)
            {
                Relay_ON();
            
            }
            
            OLED_ShowString(2, 1, "Temp:");
            OLED_ShowNum(2,6, TempH, 2);
            OLED_ShowString(2,8, ".");
            OLED_ShowNum(2 ,9, TempL, 1);
            
            OLED_ShowString(3, 1, "Humi:");
            OLED_ShowNum(3,6, HumiH, 2);
            OLED_ShowString(3,8, ".");
            OLED_ShowNum(3 ,9, HumiL, 1);
            
          
            
        }
        else
        {
            OLED_ShowString(0, 0, "read faile");
        }
    }
    

}
