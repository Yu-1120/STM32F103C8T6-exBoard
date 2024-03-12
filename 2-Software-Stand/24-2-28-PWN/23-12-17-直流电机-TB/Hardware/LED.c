#include "stm32f10x.h"                  // Device header

/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  */
void Control_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
	
	/*设置GPIO初始化后的默认电平*/
	GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4);				//设置PA1和PA2引脚为高电平
}

/**
  * 函    数：LED1开启
  * 参    数：无
  * 返 回 值：无
  */
void Control_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_3);		
    GPIO_SetBits(GPIOA, GPIO_Pin_4);		
}

/**
  * 函    数：LED1关闭
  * 参    数：无
  * 返 回 值：无
  */
void Control_OFF(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);		
    GPIO_SetBits(GPIOA, GPIO_Pin_3);		
}


