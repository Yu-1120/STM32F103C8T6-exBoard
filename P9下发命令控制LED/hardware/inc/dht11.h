#ifndef DHT11_H
#define DHT11_H

#include "stm32f10x.h"
#define DHT11_Pin GPIO_Pin_11

//PA11
#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=8<<12;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=3<<12;}
//IO操作函数   
#define	DHT11_DQ_OUT(X)  GPIO_WriteBit(GPIOA, DHT11_Pin, X)
#define	DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOA, DHT11_Pin)

uint8_t DHT11_Init(void);//初始化DHT11
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//读取数据
uint8_t DHT11_Read_Byte(void);//读取一个字节
uint8_t DHT11_Read_Bit(void);//读取一位
uint8_t DHT11_Check(void);//检测DHT11
void DHT11_Rst(void);//复位DHT11   

#endif
