#include "DHT11.h"

/**
 * @brief	DHT11 ����ģʽ
 * @param	None
 * @retval 	None
 *
 */
void DHT11_IO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // ��������
	GPIO_InitStructure.GPIO_Pin =DHT11_PIN ; // ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_DHT11,&GPIO_InitStructure);	
}


/**
 * @brief	DHT11 ���ģʽ
 * @param	None
 * @retval 	None
 *
 */
void DHT11_IO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // ������� // ��������
	GPIO_InitStructure.GPIO_Pin =DHT11_PIN ; // �������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_DHT11,&GPIO_InitStructure);
}


/**
 * @brief	����DHT11
 * @param	None
 * @retval 	None
 *
 */
void DHT11_RST(void)
{
	
	
	DHT11_IO_OUT(); // ��ֵ���ģʽ
	GPIO_ResetBits(GPIO_DHT11,DHT11_PIN); // ���͵�ƽ
	Delay_ms(20); // �������� 18ms
	GPIO_SetBits(GPIO_DHT11,DHT11_PIN);
	Delay_us(30); // ��������20 - 40 us
	GPIO_ResetBits(GPIO_DHT11,DHT11_PIN); // ���͵�ƽ
}


/**
 * @brief	���DHT11 ����Ӧ�ź�
 * @param	None
* @retval 	1:DHT11����������0:DHT11����
 *
 */
u8 DHT11_Check(void)
{
	u8 retry = 0;
	DHT11_IO_IN(); // ��������ģʽ
	// DHT11 ������ 40 - 50us
	while(GPIO_ReadInputDataBit(GPIO_DHT11,DHT11_PIN) && retry <100){
		retry++;
		Delay_us(1);
	}
	
	if(retry >= 100)
	{
		return 1;
	}else{
		retry = 0;
	}
	
	// DHT11 ���ٴ����� 40 - 50 us
	while(GPIO_ReadInputDataBit(GPIO_DHT11,DHT11_PIN) && retry < 100){
		retry++;
		Delay_us(1);
	}
	
	// ��ʱ DHT11 ���������˳����
	if(retry >= 100) 
	{
		return 0; 
	}
	
	return 1; // �豸��������
	
}


/**
 * @brief	DHT11 ��ʼ��
* @param	None
* @retval 	1:��ʾDHT11����������0:��ʾDHT11�д���
 *
 */
u8 DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	DHT11_IO_OUT(); // �������ģʽ
	DHT11_RST();  // ���Ϳ�ʼ�ź�
	return DHT11_Check();
}

/**
 * @brief	��ȡ1bit������
 * @param	None 
 * @retval 	0:�͵�ƽ��1:�ߵ�ƽ
 *
 */
u8 DHT11_ReadBit(void)
{
	u8 retry = 0;
	// �ȴ���Ϊ�͵�ƽ(�ȴ�bit��ʼ�ź�)�����͵�ƽ��ʱ��Ϊ80us
	while(GPIO_ReadInputDataBit(GPIO_DHT11,DHT11_PIN) && retry<100){
		retry++;
		Delay_us(1);
	}
	
	retry = 0;
	
	// �ȴ���Ϊ�ߵ�ƽ�����ߵ�ƽ��ʱ��Ϊ80us,֮��ʼ��������,����ȴ���100us��
	while(!GPIO_ReadInputDataBit(GPIO_DHT11,DHT11_PIN) && retry < 100){
		retry++;
		Delay_us(1);
	}
	
	// 1bit ��ʼ
	Delay_us(30); 
	
	// ��ȡ����
	// 0�źŵ�ʱ��Ϊ 26-28us
	// 1�źŵ�ʱ��Ϊ 70us
	// ���Գ���30usȥ���Ϳ���ֱ���� 0�źŻ��� 1�ź�
	if(GPIO_ReadInputDataBit(GPIO_DHT11,DHT11_PIN) == SET){
		return 1;
	}
	return 0;
}

/**
 * @brief	��ȡ1byte������
 * @param	None
 * @retval 	���ض�ȡ���ֽ�
 *
 */
u8 DHT11_ReadByte(void)
{
	u8 i = 0,Byte = 0;
	for(;i<8;i++){
		Byte <<= 1;
		Byte |= DHT11_ReadBit();
	}
	return Byte;
}

/**
 * @brief	��ȡ��ʪ������
 * @param	TempH: �����������¼�¶ȵ���������
 * @param	TempL: �����������¼�¶ȵ�С������
 * @param	HumiH: �����������¼�¶ȵ���������
 * @param	HumiL: �����������¼�¶ȵ�С������
 * @retval 	0:��ʾ��ȡ����ʧ�ܣ�1:��ʾ��ȡ���ݳɹ�
 *
 */
u8 DHT11_ReadData(u8 *TempH,u8 *TempL,u8 *HumiH,u8 *HumiL)
{
	u8 Buf[5];
	u8 i;
	DHT11_RST();
	
	if(DHT11_Check() == 1)
	{
		for(i = 0;i <5;i++){
			Buf[i] =DHT11_ReadByte();
		}
		if(Buf[0] + Buf[1] + Buf[2] + Buf[3] == Buf[4]){
			*HumiH = Buf[0];
			*HumiL = Buf[1];
			*TempH = Buf[2];
			*TempL = Buf[3];
		}
	}else{
		return 0; // ����δ��Ӧ
	}
	return 1; // �豸��ȡ���ݳɹ�
}