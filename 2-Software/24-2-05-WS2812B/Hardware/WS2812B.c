

#include "WS2812B.h"

Color_TypeDef PixelBuf[PIXEL_NUM]; //像数数据
uint8_t flag;

//晶振48M,每个nop是20.83ns
#define DELAY_20_8nS		__nop()		//1个nop是20.8ns
#define DELAY_104nS			DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS;DELAY_20_8nS //5个nop是104ns
#define Delay_320nS()		DELAY_104nS;DELAY_104nS;DELAY_104nS  //30个nop
 
/*---------------------------------------------------------------------------
@Function   :Delay_850nS
@Description:检测开关初始化
@Input      :无
@Retrun     :无
@Others     :T1H T0L 时间在  580ns~1.6us,取850ns   实测855us
----------------------------------------------------------------------------*/
void Delay_850nS(void)
{
	//进入函数所用的时间约为310ns
	DELAY_104nS;
	DELAY_104nS;
	Delay_320nS();
	DELAY_20_8nS;
}
/*---------------------------------------------------------------------------
@Function   :Delay_300uS
@Description:
@Input      :无
@Retrun     :无
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
@Description:初始化
@Input      :无
@Retrun     :无
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_Init(void)
    
{
	GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(WS2812B_RCC_AHB, ENABLE);		//开启GPIOA的时钟
    
    

	GPIO_InitStructure.GPIO_Pin = WS2812B_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(WS2812B_PORT, &GPIO_InitStructure);

    
    
   
    
	GPIO_SetBits(WS2812B_PORT, WS2812B_PIN);
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_Reset
@Description:复位
@Input      :无
@Retrun     :无
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_Reset(void)          //复位函数
{
	WS2812B_Low();
	Delay_300uS();
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_WriteByte
@Description:写一个字节
@Input      :无
@Retrun     :无
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_WriteByte(uint8_t dat)
{
	u8 i;
	for (i=0;i<8;i++)
	{
		//先发送高位
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
@Description:写入1个24bit颜色数据
@Input      :无
@Retrun     :无
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
@Description:更新显示
@Input      :无
@Retrun     :无
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

//测试延时时间
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
@Description:填充颜色
@Input      :start：开始位置;end:结束信置;pColor:颜色值
@Retrun     :无
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_FillColor(u16 start,u16 end,Color_TypeDef *pColor)
{
	if (start > end) //交换位置
	{
		u16 temp;
		temp = start;
		start = end;
		end = temp;
	}

	if (start >= PIXEL_NUM)return; //超出范围
	if (end >= PIXEL_NUM)end = PIXEL_NUM-1;

	//填充颜色值
	while(start <= end)
	{
		Copy_Color(&PixelBuf[start],pColor);
		start++;
	}
}

/*---------------------------------------------------------------------------
@Function   :WS2812B_MovePixel
@Description:循环移动像素颜色
@Input      :dir:方向;
@Retrun     :无
@Others     :
----------------------------------------------------------------------------*/
void WS2812B_MovePixel(u8 dir)
{
	Color_TypeDef temp;
	u8 i;

	if (dir) //向左移动
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
	else  //向右移动
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

