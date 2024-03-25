#ifndef DHT11_H
#define DHT11_H

#include "stm32f10x.h"

#define DT GPIO_Pin_7
      
#define DHT11_IO_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<28;}
#define DHT11_IO_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<28;} 

#define	DHT11_DQ_OUT(X)  GPIO_WriteBit(GPIOB, DT, X)
#define	DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOB, DT)

uint8_t DHT11_Init(void);//��ʼ��DHT11
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//��ȡ����
uint8_t DHT11_Read_Byte(void);//��ȡһ���ֽ�
uint8_t DHT11_Read_Bit(void);//��ȡһλ
uint8_t DHT11_Check(void);//���DHT11
void DHT11_Rst(void);//��λDHT11   

#endif
