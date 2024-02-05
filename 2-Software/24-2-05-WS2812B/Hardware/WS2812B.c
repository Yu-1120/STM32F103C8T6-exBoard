

#include "WS2812B.h"

Color_TypeDef PixelBuf[PIXEL_NUM]; //��������
uint8_t flag;

//����48M,ÿ��nop��20.83ns
#define DELAY_20_8nS		__nop()		//1��nop��20.8ns
#define DELAY_104nS			DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS //5��nop��104ns
#define Delay_320nS()		DELAY_104nS;DELAY_104nS;DELAY_104nS  //30��nop
 
/*---------------------------------------------------------------------------
@Function   :Delay_850nS
@Description:��⿪�س�ʼ��
@Input      :��
@Retrun     :��
@Others     :T1H T0L ʱ����  580ns~1.6us,ȡ850ns   ʵ��855us
----------------------------------------------------------------------------*/
void Delay_850nS(void)
{
	//���뺯�����õ�ʱ��ԼΪ310ns
	DELAY_104nS;
	DELAY_104nS;
	Delay_320nS();
	DELAY_20_8nS;
}
/*---------------------------------------------------------------------------
@Function   :Delay_300uS
@Description:
@Input      :��
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void Delay_300uS(void)
{
	uint8_t i;
	while(i--)
	{
		Delay_320nS();
	}
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_Init
@Description:��ʼ��
@Input      :��
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_Init(void)
    
{
	GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(WS2812B_RCC_AHB, ENABLE);		//����GPIOA��ʱ��
    
    

	GPIO_InitStructure.GPIO_Pin = WS2812B_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(WS2812B_PORT, &GPIO_InitStructure);

    
    
   
    
	GPIO_SetBits(WS2812B_PORT, WS2812B_PIN);
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_Reset
@Description:��λ
@Input      :��
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_Reset(void)          //��λ����
{
	WS2812B_Low();
	Delay_300uS();
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_WriteByte
@Description:дһ���ֽ�
@Input      :��
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_WriteByte(uint8_t dat)
{
	u8 i;
	for (i=0;i<8;i++)
	{
		//�ȷ��͸�λ
		if (dat & 0x80) //1
		{
			WS2812B_Hi();
			Delay_850nS(); //T1H
			WS2812B_Low();	
			Delay_320nS(); //T1L
		}
		else	//0
		{
			WS2812B_Hi();
			Delay_320nS(); //T0H
			WS2812B_Low();	
			Delay_850nS(); //T0L
		}
		dat<<=1;
	}
}


/*---------------------------------------------------------------------------
@Function   :WS2812B_WriteColor
@Description:д��1��24bit��ɫ����
@Input      :��
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_WriteColor(Color_TypeDef *pColor)
{
	WS2812B_WriteByte(pColor->G);
	WS2812B_WriteByte(pColor->R);
	WS2812B_WriteByte(pColor->B);
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_RefreshPixel
@Description:������ʾ
@Input      :��
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_RefreshPixel(void)
{
	u8 i;

	for(i=0;i<PIXEL_NUM;i++)
	{
		WS2812B_WriteColor(&PixelBuf[i]);
	}
}

//----------------------------------------
void WS2812B_Test(void)
{
	u8 i;
	Color_TypeDef temp;
	temp.B = 0x50;
	temp.R = 0x60;
	temp.G = 0xff;

	for(i=0;i<60;i++)
	{
		WS2812B_WriteColor(&temp);
	}
}

//������ʱʱ��
void WS2812B_Test2(void)
{
	WS2812B_Hi();
	Delay_850nS();
	WS2812B_Low();
}

//============================================================================
void Copy_Color(Color_TypeDef *pDst,Color_TypeDef *pScr)
{
	pDst->R = pScr->R;
	pDst->G = pScr->G;
	pDst->B = pScr->B;
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_FillColor
@Description:�����ɫ
@Input      :start����ʼλ��;end:��������;pColor:��ɫֵ
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_FillColor(u16 start,u16 end,Color_TypeDef *pColor)
{
	if (start > end) //����λ��
	{
		u16 temp;
		temp = start;
		start = end;
		end = temp;
	}

	if (start >= PIXEL_NUM)return; //������Χ
	if (end >= PIXEL_NUM)end = PIXEL_NUM-1;

	//�����ɫֵ
	while(start <= end)
	{
		Copy_Color(&PixelBuf[start],pColor);
		start++;
	}
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_MovePixel
@Description:ѭ���ƶ�������ɫ
@Input      :dir:����;
@Retrun     :��
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_MovePixel(u8 dir)
{
	Color_TypeDef temp;
	u8 i;

	if (dir) //�����ƶ�
	{
		Copy_Color(&temp,&PixelBuf[PIXEL_NUM-1]);

		i = PIXEL_NUM-1;
		while(i)
		{
			 Copy_Color(&PixelBuf[i],&PixelBuf[i-1]);
			 i--;
		}
		Copy_Color(&PixelBuf[0],&temp);
	}
	else  //�����ƶ�
	{
		Copy_Color(&temp,&PixelBuf[0]);

		i = 0;
		while(i < (PIXEL_NUM-1))
		{
			Copy_Color(&PixelBuf[i],&PixelBuf[i+1]);
			i++;
		}
		Copy_Color(&PixelBuf[PIXEL_NUM-1],&temp);
	}
}

//----------------------------------END OF FILE------------------------------

