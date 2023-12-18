#include "stm32f10x.h"  
#include "EC11.h"
#include "Delay.h"
#include "LED.h"
//GPIO≥ı ºªØ
#include "OLED.h"



void EC11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		
    
    
  	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = EC11_GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EC11_GPIO, &GPIO_InitStructure);						

	GPIO_SetBits(EC11_GPIO, EC11_GPIO_Pin_3 );				
    
    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = EC11_GPIO_Pin_4 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EC11_GPIO, &GPIO_InitStructure);						
	

	GPIO_SetBits(EC11_GPIO, EC11_GPIO_Pin_4 );				
    
  
}
  



    
    





