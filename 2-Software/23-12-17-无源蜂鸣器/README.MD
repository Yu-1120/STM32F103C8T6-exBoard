

[live.csdn.net/v/363133](https://live.csdn.net/v/363133)





### 无源蜂鸣器硬件











![image-20240204144939677](README.assets/image-20240204144939677.png)



## 更新时间

| 时间                 | 说明         |      |
| -------------------- | ------------ | ---- |
| 2024年2月6日00点11分 | 代码测试成功 |      |
|                      |              |      |
|                      |              |      |





### 代码

[STM32 使用STM32F103控制无源蜂鸣器发声播放音乐_stm32 无源蜂鸣器 音阶-CSDN博客](https://blog.csdn.net/qq_28056277/article/details/85165731)



#### main.c

```c
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Beep.h"
uint8_t KeyNum;		//定义用于接收按键键码的变量
int main(void)
{
	/*模块初始化*/
	LED_Init();		//LED初始化
	Key_Init();		//按键初始化
	LED1_OFF();			//LED1翻转
    BEEP_Init();
	while (1)
	{
        
        

        GPIO_ResetBits(BEEP_GPIO, GPIO_Pin_11);		//将PB12引脚设置为低电平，蜂鸣器鸣叫
		Delay_ms(100);							//延时100ms
		GPIO_SetBits(BEEP_GPIO, GPIO_Pin_11);		//将PB12引脚设置为高电平，蜂鸣器停止
		Delay_ms(100);							//延时100ms
		GPIO_ResetBits(BEEP_GPIO, GPIO_Pin_11);		//将PB12引脚设置为低电平，蜂鸣器鸣叫
		Delay_ms(100);							//延时100ms
		GPIO_SetBits(BEEP_GPIO, GPIO_Pin_11);		//将PB12引脚设置为高电平，蜂鸣器停止
		Delay_ms(700);							//延时700ms
        

   	    KeyNum = Key_GetNum();		
		
		if (KeyNum == 2)			
		{
			LED1_Turn();
		}
		

        
	
	}
}

```







#### Beep.c



```
#include "stm32f10x.h"                  // Device header
#include "Beep.h"
 int melody[] = {50, 50, 50, 50, 200, 200, 200, 400, 400, 500, 500, 500};
void BEEP_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BEEP_GPIO, &GPIO_InitStructure);						//将PA1和PA2引脚初始化为推挽输出
	
	/*设置GPIO初始化后的默认电平*/
	GPIO_SetBits(BEEP_GPIO, BEEP_PIN );				//设置PA1和PA2引脚为高电平
}

/**
  * 函    数：LED1开启
  * 参    数：无
  * 返 回 值：无
  */
void BEEP_ON(void)
{
	GPIO_ResetBits(BEEP_GPIO, BEEP_PIN);		//设置PA1引脚为低电平
}

/**
  * 函    数：LED1关闭
  * 参    数：无
  * 返 回 值：无
  */
void BEEP_OFF(void)
{
	GPIO_SetBits(BEEP_GPIO, BEEP_PIN);		//设置PA1引脚为高电平
}

/**
  * 函    数：LED1状态翻转
  * 参    数：无
  * 返 回 值：无
  */

void Sound(u16 frq)
{
    u32 time;
    if(frq != 1000)
    {
        time = 500000/((u32)frq);
        BEEP_OFF();
        Delay_us(time);
        BEEP_ON();
        Delay_us(time);
    }else
        Delay_us(1000);
}
void Sound2(u16 time)
{
    BEEP_OFF();
    Delay_ms(time);
    BEEP_ON();
    Delay_ms(time);
}

void play_successful(void)
{
    int id=0;
    for(id = 0 ;id < 12 ;id++)
    {
        Sound2(melody[id]);
    }
}
void play_failed(void)
{
    int id=0;
    for(id = 11 ;id >=0 ;id--)
    {
        Sound2(melody[id]);
    }
}
void play_music(void)
{    
//红海情歌
//    uc16 tone[] = {247,262,294,330,349,392,440,294,523,587,659,698,784,1000};    
//    u8 music[]={5,5,6,8,7,6,5,6,13,13,5,5,6,8,7,6,5,3,13,13,2,2,3,5,3,5,6,3,2,1,6,6,5,6,5,3,6,5,13,13,
//                  5,5,6,8,7,6,5,6,13,13,5,5,6,8,7,6,5,3,13,13,2,2,3,5,3,5,6,3,2,1,6,6,5,6,5,3,6,1,    
//              13,8,9,10,10,9,8,10,9,8,6,13,6,8,9,9,8,6,9,8,6,5,13,2,3,5,5,3,5,5,6,8,7,6,6,10,9,9,8,6,5,6,8  };            
//    u8 time[] = {2,4,2,2,2,2,2,8,4, 4,2,4,2,2,2,2,2,8,4, 4, 2,4,2,4,2,2,4,2,2,8,2,4,2,2,2,2,2,8,4 ,4, 
//                2,4,2,2,2,2,2,8,4, 4,2,4,2,2,2,2,2,8,4,4,2,4,2,4,2,2,4,2,2,8,2,4,2,2,2,2,2,8,
//                4,2,2,2,4,2,2,2,2,2,8,4,2,2,2,4,2,2,2,2,2,8,4,2,2,2,4,2,2,5,2,6,2,4,2,2,2,4,2,4,2,2,12  };

/*************************************************************************************************************************/
    
//生日快乐    
                  // 0   1   2   3   4   5   6   7  低1  低2 低3 低4 低5 低6低7
    uc16 tone[] ={250,262,294,330,350,393,441,495,525,589,661,700,786,882,990}; //音调        
    u8 music[]={5,5,6,5,8,7,5,5,6,5,9,8,5,5,12,10,8,7,6,11,
                  11,10,8,9,8,5,5,8,5,5,12,10,8,7,6,11,11,10,8,9,8    //乐谱音调
    };     
        u8 time[] = {1,2,2,2,2,4,1,2,2,2,2,4,1,2,2,2,1,4,
                      4,1,2,2,2,2,4,1,2,4,1,2,2,2,1,4, 4,1,2,2,2,2,4,4        //节拍时间
        }; 
                    
    u32 yanshi;
    u16 i,e;
    yanshi = 10;
    for(i=0;i<sizeof(music)/sizeof(music[0]);i++){
        for(e=0;e<((u16)time[i])*tone[music[i]]/yanshi;e++){
            Sound((u32)tone[music[i]]);
        }    
    }
}






```







#### Beep.h

```
#ifndef __BEEP_H
#define __BEEP_H

#include "Delay.h"
#define  BEEP_PIN  GPIO_Pin_11
#define  BEEP_GPIO  GPIOB

void BEEP_Init(void);
void BEEP_ON(void);
void BEEP_OFF(void);
void Sound(u16 frq);
void Sound2(u16 time);
void play_music(void);
void play_successful(void);
void play_failed(void);

#endif

```

