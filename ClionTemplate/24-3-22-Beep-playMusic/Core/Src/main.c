#include "stm32f10x.h"
#include "USART.h"
#include "Delay.h"
#include "string.h"
#include "LED.h"
#include "Beep.h"
uint8_t KeyNum;		//�������ڽ��հ�������ı���
int main(void)
{
    /*ģ���ʼ��*/
    LED_Init();		//LED��ʼ��
    LED1_OFF();			//LED1��ת
    BEEP_Init();
    Sound(500);//���� //Ҫ��forѭ����ȻûЧ��
    while (1)
    {

        //play_music();
    }
}

