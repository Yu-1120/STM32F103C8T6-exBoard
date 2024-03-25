#include "stm32f10x.h"                  // Device header
#include "LED.h"
/**
  * ��    ����LED��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void LED_Init(void)
{
    /*����ʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		//����GPIOA��ʱ��

    /*GPIO��ʼ��*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED_PIN ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED_GPIO, &GPIO_InitStructure);						//��PA1��PA2���ų�ʼ��Ϊ�������

    /*����GPIO��ʼ�����Ĭ�ϵ�ƽ*/
    GPIO_SetBits(LED_GPIO, LED_PIN );				//����PA1��PA2����Ϊ�ߵ�ƽ
}

/**
  * ��    ����LED1����
  * ��    ������
  * �� �� ֵ����
  */
void LED1_ON(void)
{
    GPIO_ResetBits(LED_GPIO, LED_PIN);		//����PA1����Ϊ�͵�ƽ
}

/**
  * ��    ����LED1�ر�
  * ��    ������
  * �� �� ֵ����
  */
void LED1_OFF(void)
{
    GPIO_SetBits(LED_GPIO, LED_PIN);		//����PA1����Ϊ�ߵ�ƽ
}

/**
  * ��    ����LED1״̬��ת
  * ��    ������
  * �� �� ֵ����
  */
void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(LED_GPIO, LED_PIN) == 0)		//��ȡ����Ĵ�����״̬�������ǰ��������͵�ƽ
    {
        GPIO_SetBits(LED_GPIO, LED_PIN);					//������PA1����Ϊ�ߵ�ƽ
    }
    else													//���򣬼���ǰ��������ߵ�ƽ
    {
        GPIO_ResetBits(LED_GPIO, LED_PIN);					//������PA1����Ϊ�͵�ƽ
    }
}

