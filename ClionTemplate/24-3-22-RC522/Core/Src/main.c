#include "stm32f10x.h"


#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "RC522.h"
#include "USART1.h"
char status;
unsigned char snr, buf[16], TagType[2], SelectedSnr[4], DefaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//2024年3月20日测试成功，可以读写
void GPIO_ini()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO Clock */
  RCC_APB2PeriphClockCmd(MF522_RST_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_RST_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_RST_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_APB2PeriphClockCmd(MF522_MISO_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_MISO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_MISO_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_APB2PeriphClockCmd(MF522_MOSI_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_MOSI_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_MOSI_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_APB2PeriphClockCmd(MF522_SCK_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_SCK_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_APB2PeriphClockCmd(MF522_NSS_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = MF522_NSS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(MF522_NSS_PORT, &GPIO_InitStructure);
	
  /* Enable the GPIO Clock */
  RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);

  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = LED_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void InitializeSystem()
{
	LED_OFF;
	delay_10ms(10);
	PcdReset();
	PcdAntennaOff(); 
	PcdAntennaOn();  
	M500PcdConfigISOType( 'A' );
	LED_ON;
	delay_10ms(10);	
	LED_OFF;
	delay_10ms(10);
	LED_ON;
	delay_10ms(10);	
	LED_OFF;
}

int main(void)
{
    Usart1_Init(115200);     //串口1功能初始化

    OLED_Init();		//OLED初始化
	GPIO_ini();  
    InitializeSystem( );
    while(1)
    {  

            		status= PcdRequest(REQ_ALL,TagType);
		if(!status)
		{
			status = PcdAnticoll(SelectedSnr);
			if(!status)
			{
				status=PcdSelect(SelectedSnr);
				if(!status)
				{
                    
                    OLED_ShowString(1,1,"wirte success");
					snr = 1;  //扇区号1
                    status = PcdAuthState(KEYA, (snr*4+3), DefaultKey, SelectedSnr);// 校验1扇区密码，密码位于每一扇区第3块
                    OLED_ShowNum(2,1,KEYA,17);
					{
						if(!status)
						{
                          
                            OLED_ShowString(1,1,"wirte success");
							status = PcdRead((snr*4+0), buf);  // 读卡，读取1扇区0块数据到buf[0]-buf[16] 
                             
							//status = PcdWrite((snr*4+0), buf);  // 写卡，将buf[0]-buf[16]写入1扇区0块
							if(!status)
							{
								//读写成功，点亮LED
								LED_ON;	
								WaitCardOff();
							}
						}
					}
				}
			}
		}	
		LED_OFF; 
        
    }
}
