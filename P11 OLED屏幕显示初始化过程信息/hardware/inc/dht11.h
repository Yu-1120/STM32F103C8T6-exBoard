#ifndef DHT11_H
#define DHT11_H

#include "stm32f10x.h"

#define DT GPIO_Pin_7
      
#define DHT11_IO_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<28;}
#define DHT11_IO_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<28;} 

#define	DHT11_DQ_OUT(X)  GPIO_WriteBit(GPIOB, DT, X)
#define	DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOB, DT)

uint8_t DHT11_Init(void);//初始化DHT11
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//读取数据
uint8_t DHT11_Read_Byte(void);//读取一个字节
uint8_t DHT11_Read_Bit(void);//读取一位
uint8_t DHT11_Check(void);//检测DHT11
void DHT11_Rst(void);//复位DHT11   

#endif
