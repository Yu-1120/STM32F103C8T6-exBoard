#ifndef DHT11_H
#define DHT11_H

#include "stm32f10x.h"
#define DHT11_Pin GPIO_Pin_11

//PA11
#define DHT11_IO_IN()  {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=8<<12;}
#define DHT11_IO_OUT() {GPIOA->CRH&=0XFFFF0FFF;GPIOA->CRH|=3<<12;}
//IO��������   
#define	DHT11_DQ_OUT(X)  GPIO_WriteBit(GPIOA, DHT11_Pin, X)
#define	DHT11_DQ_IN  GPIO_ReadInputDataBit(GPIOA, DHT11_Pin)

uint8_t DHT11_Init(void);//��ʼ��DHT11
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);//��ȡ����
uint8_t DHT11_Read_Byte(void);//��ȡһ���ֽ�
uint8_t DHT11_Read_Bit(void);//��ȡһλ
uint8_t DHT11_Check(void);//���DHT11
void DHT11_Rst(void);//��λDHT11   

#endif
