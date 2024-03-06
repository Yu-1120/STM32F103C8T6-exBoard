# 2-EXTI外部中断的配置 	

## STM32F103C8T6

EXTI，就类似按键，就是检测 引脚的电平然后进入中断的

有68个中断屏蔽通道（中断源）





## NVIC管理中断

来管理中断，有16个中断优先级

嵌套中断向量控制器

分配中断和配置中断优先级

内核外设



### 抢占优先级

越低优先级越高

### 响应优先级

越高，优先级越高

内核中断

比如像复位中断这些，比较高深，一般咱们用不到这些中断





PVD中断

就是检测你的电压，如果你的电压的不足，就知道你的电池是不是快没电， 去保持一下数据

在低电压的时候进入，在电压变高的时候，通过外部中断退出停止模式，



中断函数， 它的地址是由编译器来分配的，是不固定的，但是我们的中断调转，由于硬件限制，只能跳到固定的地址执行程序。为了让硬件跳到一个不固定的中断函数里就要一个表，这个表就是中断向量表。但是这些编译器都帮我们做了，就不需要我们去提供这个表了



## EXTI

### 下降沿

就是高电平变到低电平的瞬间触发中断

### 双边沿

就是上升沿或者下降沿都可以去触发中断

### 软件触发

就是软件上一句代码就可以触发中断

但是相同的Pin不能触发中断了，比如PC3是触发中断的，但是PB3就不可以去触发中断了（PA0和PB0,PB1和PA1不能同时用），只能选择其中一个作为芯片引脚，16个Pin外加4个比较特别引脚

因为这里有AFIO的，类似一个数据选择器的结构，同时的PA0,PB0,PC0中的只能由一个去选择出来，到EXTI0上放，

ST公司觉得20个通道太多了，就把5~9，10~15,给分别分到一个通道里面去

### AFIO复用选择器

外部中断有个功能，就是从低功耗模式的停止模式下唤醒STM32

### PVD中断	 

RTC也是一样，需要一个闹钟响的时候再唤醒，需要借助外部中断触发响应的方式，如果选择中断的响应，会去CPU那里去响应选择事件响应的时，会通向其他的外设那里去（触发ADC，触发DMA	

### 红外的输出，接收的时候需要外部中断来读取

但是不推荐用外部中断去读取按键，因为外部中断不好处理按键抖动和松手检测，但是可以去用定时器读取按键





```c
#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;                //全局变量，用于计数

/**
  * 函    数：计数传感器初始化
  * 参    数：无
  * 返 回 值：无
  */
void CountSensor_Init(void)
{
    /*开启时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);        //开启GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //开启AFIO的时钟，外部中断必须开启AFIO的时钟
    
    /*GPIO初始化*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);                        //将PB14引脚初始化为上拉输入
    
    /*AFIO选择中断引脚*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);//将外部中断的14号线映射到GPIOB，即选择PB14为外部中断引脚
    
    /*EXTI初始化*/
    EXTI_InitTypeDef EXTI_InitStructure;                        //定义结构体变量
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;                    //选择配置外部中断的14号线
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                    //指定外部中断线使能
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;            //指定外部中断线为中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;        //指定外部中断线为下降沿触发
    EXTI_Init(&EXTI_InitStructure);                                //将结构体变量交给EXTI_Init，配置EXTI外设
    
    /*NVIC中断分组*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                //配置NVIC为分组2
                                                                //即抢占优先级范围：0~3，响应优先级范围：0~3
                                                                //此分组配置在整个工程中仅需调用一次
                                                                //若有多个中断，可以把此代码放在main函数内，while循环之前
                                                                //若调用多次配置分组的代码，则后执行的配置会覆盖先执行的配置
    
    /*NVIC配置*/
    NVIC_InitTypeDef NVIC_InitStructure;                        //定义结构体变量
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;        //选择配置NVIC的EXTI15_10线
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                //指定NVIC线路使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;    //指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            //指定NVIC线路的响应优先级为1
    NVIC_Init(&NVIC_InitStructure);                                //将结构体变量交给NVIC_Init，配置NVIC外设
}

/**
  * 函    数：获取计数传感器的计数值
  * 参    数：无
  * 返 回 值：计数值，范围：0~65535
  */
uint16_t CountSensor_Get(void)
{
    return CountSensor_Count;
}

/**
  * 函    数：EXTI15_10外部中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line13) == SET)        //判断是否是外部中断14号线触发的中断
    {
        /*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
        {
            CountSensor_Count ++;                    //计数值自增一次
        }
        EXTI_ClearITPendingBit(EXTI_Line13);        //清除外部中断14号线的中断标志位
                                                    //中断标志位必须清除
                                                    //否则中断将连续不断地触发，导致主程序卡死
    }
}

```

### 如果需要修改外部中断的需要

### 修改GPIO口的位置

```C
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13  
```



### AFIO选择中断引脚



```C
    /*AFIO选择中断引脚*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
    
```



### 选择配置外部中断的14号线

```C
EXTI_InitStructure.EXTI_Line = EXTI_Line13;        
```



### 选择配置NVIC的EXTI15_10线

```C
NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;        
```



### EXTI15_10外部中断函数

```C
void EXTI15_10_IRQHandler(void)
```



### 中断服务函数处完后需要挂起

```C
void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line13) == SET)        //判断是否是外部中断14号线触发的中断
    {
        /*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
        {
            CountSensor_Count ++;                    //计数值自增一次
        }
        EXTI_ClearITPendingBit(EXTI_Line13);        //清除外部中断14号线的中断标志位
                                                    //中断标志位必须清除
                                                    //否则中断将连续不断地触发，导致主程序卡死
    }
}

```

