#include "stm32f10x.h"                  // Device header

#include "OLED.h"

int main(void)
{
	/*ģ���ʼ��*/
	OLED_Init();		//OLED��ʼ��
		/*OLED��ʾ*/
	OLED_ShowChar(1, 1, 'A');				//1��1����ʾ�ַ�A

	OLED_ShowString(1, 3, "HelloWorld!");	//1��3����ʾ�ַ���HelloWorld!


	OLED_ShowNum(2, 1, 12345, 5);			//2��1����ʾʮ��������12345������Ϊ5

	OLED_ShowSignedNum(2, 7, -66, 2);		//2��7����ʾ�з���ʮ��������-66������Ϊ2

	OLED_ShowHexNum(3, 1, 0xAA55, 4);		//3��1����ʾʮ����������0xA5A5������Ϊ4

	OLED_ShowBinNum(4, 1, 0xAA55, 16);		//4��1����ʾ����������0xA5A5������Ϊ16
											//C�����޷�ֱ��д�����������֣�����Ҫ��ʮ�����Ʊ�ʾ

	while (1)
	{

	}
}
