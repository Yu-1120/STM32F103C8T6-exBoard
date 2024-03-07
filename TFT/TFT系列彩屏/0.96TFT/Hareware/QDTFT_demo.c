/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "QDTFT_demo.h"
#include "Picture.h"

unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};
void Redraw_Mainmenu(void)
{

	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(8,0,BLUE,GRAY0,"����ģ��");
	Gui_DrawFont_GBK16(8,20,RED,GRAY0,"Һ������");

	DisplayButtonUp(0,38,80,58); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(8,40,YELLOW,GRAY0,"��ɫ���");

	DisplayButtonUp(0,68,80,88); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(8,60,BLUE,GRAY0,"������ʾ");

	DisplayButtonUp(0,98,80,118); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(80,20,RED,GRAY0,"ͼƬ��ʾ");
	Delay_ms(1500);
}

void Num_Test(void)
{
	u8 i=0;
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(8,20,RED,GRAY0,"Num Test");
	Delay_ms(1000);
	Lcd_Clear(GRAY0);

	for(i=0;i<10;i++)
	{
	Gui_DrawFont_Num32((i%4)*40,32*(i/4)+5,RED,GRAY0,Num[i+1]);
	Delay_ms(100);
	}
	
}
void LCD_ShowNumTES(void)
{
	u8 i=0;
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(8,20,RED,GRAY0,"SHOW_Num");
	Delay_ms(1000);
	Lcd_Clear(GRAY0);

	for(i=0;i<255;i++)
	{
        LCD_ShowNum(0,0,i,3,Purple);
        LCD_ShowNum(0,20,i,3,Purple);
        LCD_ShowNum(0,40,i,3,Purple);
        LCD_ShowNum(0,60,i,3,Purple);


	Delay_ms(10);
	}
	
}


void Font_Test(void)
{
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(8,10,BLUE,GRAY0,"������ʾ");

	Delay_ms(1000);
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(8,0,RED,GRAY0,"���ش�ѧ");
//	Gui_DrawFont_GBK16(8,20,BLUE,GRAY0,"������ʾ");
//	Gui_DrawFont_GBK16(8,40,RED,GRAY0, "����֧��");
//	Gui_DrawFont_GBK16(0,60,BLUE,GRAY0,"Tel:88888888888");
//	Gui_DrawFont_GBK16(0,80,RED,GRAY0, "QQ:666666666");	
	Delay_ms(1800);	
}

void Color_Test(void)
{
	u8 i=1;
	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(4,10,BLUE,GRAY0,"Color Test");
	Delay_ms(200);

	while(i--)
	{
		Lcd_Clear(WHITE);
		Lcd_Clear(BLACK);
		Lcd_Clear(RED);
	  	Lcd_Clear(GREEN);
	  	Lcd_Clear(BLUE);
	}		
}

//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
void showimage(const unsigned char *p) //��ʾ64*64 QQͼƬ
{
  	int i,j,k; 
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //����  
	
	for(k=0;k<2;k++)
	{
	   	for(j=0;j<4;j++)
		{	
			Lcd_SetRegion(64*j,64*k,64*j+63,64*k+63);		//��������
		    for(i=0;i<64*64;i++)
			 {	
			 	picL=*(p+i*2);	//���ݵ�λ��ǰ
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}
void QDTFT_Test_Demo(void)
{
//    Lcd_Init();
//    LCD_BL_SET ;
//    LCD_CS_CLR ;
//    //  LCD_CS_SET ;//ͨ��IO���Ʊ�����				
//    Redraw_Mainmenu();//�������˵�(�����������ڷֱ��ʳ�������ֵ�����޷���ʾ)
//    Color_Test();//�򵥴�ɫ������
//    Num_Test();//������������
   // Font_Test();//��Ӣ����ʾ����		
    showimage(gImage_1);//ͼƬ��ʾʾ��
//    Delay_ms(1200);
//    LCD_ShowNumTES();
}
