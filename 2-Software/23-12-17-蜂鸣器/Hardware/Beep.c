#include "stm32f10x.h"                  // Device header
#include "Beep.h"

void BEEP_Init(void)
{
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//����GPIOA��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BEEP_GPIO, &GPIO_InitStructure);						//��PA1��PA2���ų�ʼ��Ϊ�������
	
	/*����GPIO��ʼ�����Ĭ�ϵ�ƽ*/
	GPIO_SetBits(BEEP_GPIO, BEEP_PIN );				//����PA1��PA2����Ϊ�ߵ�ƽ
}

/**
  * ��    ����LED1����
  * ��    ������
  * �� �� ֵ����
  */
void BEEP_ON(void)
{
	GPIO_ResetBits(BEEP_GPIO, BEEP_PIN);		//����PA1����Ϊ�͵�ƽ
}

/**
  * ��    ����LED1�ر�
  * ��    ������
  * �� �� ֵ����
  */
void BEEP_OFF(void)
{
	GPIO_SetBits(BEEP_GPIO, BEEP_PIN);		//����PA1����Ϊ�ߵ�ƽ
}

/**
  * ��    ����LED1״̬��ת
  * ��    ������
  * �� �� ֵ����
  */

