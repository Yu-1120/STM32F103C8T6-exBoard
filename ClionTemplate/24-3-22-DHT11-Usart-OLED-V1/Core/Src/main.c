#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "DHT11.h"
extern unsigned int rec_data[4];
int main(void)
{
    OLED_Init();

    while (1)
    {
        Delay_ms(200);
        DHT11_REC_Data();
        OLED_ShowNum(10,15,rec_data[0],2,OLED_8X16);
        OLED_ShowNum(30,15,rec_data[1],2,OLED_8X16);


        OLED_ShowNum(10,40,rec_data[2],2,OLED_8X16);
        OLED_ShowNum(30,40,rec_data[3],2,OLED_8X16);
        OLED_Update();
    }
}

