#include "stm32f10x.h"                  // Device header
#include "LED.h"
/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  */
#define  RCC_LED RCC_APB2Periph_GPIOC
#define  LED_PORT  GPIOC
#define  LED_PIN  GPIO_Pin_13

void LED_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_LED, ENABLE);		
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);						
	
	/*设置GPIO初始化后的默认电平*/
	GPIO_SetBits(LED_PORT, LED_PIN );				
}

/**
  * 函    数：LED1开启
  * 参    数：无
  * 返 回 值：无
  */
void LED1_ON(void)
{
	GPIO_ResetBits(LED_PORT, LED_PIN);		
}

/**
  * 函    数：LED1关闭
  * 参    数：无
  * 返 回 值：无
  */
void LED1_OFF(void)
{
	GPIO_SetBits(LED_PORT, LED_PIN);		//设置PA1引脚为高电平
}

/**
  * 函    数：LED1状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(LED_PORT, LED_PIN) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(LED_PORT, LED_PIN);					//则设置PA1引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(LED_PORT, LED_PIN);					//则设置PA1引脚为低电平
	}
}

