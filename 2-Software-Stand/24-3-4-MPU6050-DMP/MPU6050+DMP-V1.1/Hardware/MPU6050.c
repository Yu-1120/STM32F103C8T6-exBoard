#include "stm32f10x.h"                  // Device header
#include "Delay.h"
//起始 终止 发送一个字节 接受一个字节 发送应答 接收应答
#define MPU6050_SCL GPIO_Pin_13
#define MPU6050_SDA GPIO_Pin_12
struct MPU6050{
	short int accx;
	short int accy;
	short int accz;
	short int gyrox;
	short int gyroy;
	short int gyroz;
	short int temp;
};

void MPU6050_I2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = MPU6050_SDA | MPU6050_SCL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, MPU6050_SDA | MPU6050_SCL);
}

void MPU6050_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, MPU6050_SCL, (BitAction)BitValue);

}

void MPU6050_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, MPU6050_SDA, (BitAction)BitValue);
	
}

uint8_t MPU6050_R_SDA(void)
{
	uint8_t Flag;

	Flag = GPIO_ReadInputDataBit(GPIOB, MPU6050_SDA);
	return Flag;
}
	
void MPU6050_I2C_S(void)
{
	MPU6050_W_SDA(1);
	MPU6050_W_SCL(1);
	
	MPU6050_W_SDA(0);
	MPU6050_W_SCL(0);
}

void MPU6050_I2C_P(void)
{
	MPU6050_W_SDA(0);
	
	MPU6050_W_SCL(1);
	MPU6050_W_SDA(1);
}

void MPU6050_I2C_SendByte(uint8_t byte)
{
	for(uint8_t i=0;i<8;i++)
	{
		MPU6050_W_SDA(byte & (0x80>>i));
		MPU6050_W_SCL(1);
		MPU6050_W_SCL(0);
	}
}

uint8_t MPU6050_I2C_ReadByte(void)
{
	uint8_t byte=0x00;
	MPU6050_W_SDA(1);
	for(uint8_t i=0;i<8;i++)
	{
		MPU6050_W_SCL(1);
		if(MPU6050_R_SDA()==1) byte |= 0x80>>i;
		MPU6050_W_SCL(0);
	}
	return byte;
}

void MPU6050_I2C_SendAck(uint8_t Ack)
{
	MPU6050_W_SDA(Ack);
	MPU6050_W_SCL(1);
	MPU6050_W_SCL(0);
}

uint8_t MPU6050_I2C_ReadAck(void)
{
	uint8_t Ack;
	MPU6050_W_SDA(1);

	MPU6050_W_SCL(1);
	Ack = MPU6050_R_SDA();
	MPU6050_W_SCL(0);
	return Ack;
}

void MPU6050_WriteReg(uint8_t Reg, uint8_t data)
{
	MPU6050_I2C_S();
	MPU6050_I2C_SendByte(0XD0);
	MPU6050_I2C_ReadAck();
	MPU6050_I2C_SendByte(Reg);
	MPU6050_I2C_ReadAck();
	MPU6050_I2C_SendByte(data);
	MPU6050_I2C_ReadAck();
	MPU6050_I2C_P();
}

uint8_t MPU6050_ReadReg(uint8_t reg)
{
	uint8_t Data;
	MPU6050_I2C_S();
	MPU6050_I2C_SendByte(0XD0);
	MPU6050_I2C_ReadAck();
	MPU6050_I2C_SendByte(reg);
	MPU6050_I2C_ReadAck();
	MPU6050_I2C_S();
	MPU6050_I2C_SendByte(0XD1);
	MPU6050_I2C_ReadAck();
	Data = MPU6050_I2C_ReadByte();
	MPU6050_I2C_SendAck(1);
	MPU6050_I2C_P();
	
	return Data;
}

uint8_t MPU6050_Burst_Write(uint8_t Addr, uint8_t reg, uint8_t len, uint8_t const *buf)
{
	
	MPU6050_I2C_S();
	MPU6050_I2C_SendByte((Addr<<1)|0);
	MPU6050_I2C_ReadAck();
	MPU6050_I2C_SendByte(reg);
	MPU6050_I2C_ReadAck();
	
	while(len--)
	{
		MPU6050_I2C_SendByte(*(buf++));
		MPU6050_I2C_ReadAck();
	}
	MPU6050_I2C_P();
	return 0;
}
	


uint8_t MPU6050_Burst_Read(uint8_t Addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	MPU6050_I2C_S();
	MPU6050_I2C_SendByte((Addr<<1)|0);
	MPU6050_I2C_ReadAck();
	MPU6050_I2C_SendByte(reg);
	MPU6050_I2C_ReadAck();
	MPU6050_I2C_S();
	MPU6050_I2C_SendByte((Addr<<1)|1);
	MPU6050_I2C_ReadAck();
	while(len)
	{
		*(buf++) = MPU6050_I2C_ReadByte();

		switch(len){
			case 1:MPU6050_I2C_SendAck(1);break;
			default:MPU6050_I2C_SendAck(0);break;
		}
		len--;
	}
	MPU6050_I2C_P();
	return 0;
}

void MPU_6050_Init(void)
{
	MPU6050_I2C_Init();
	MPU6050_WriteReg(0x6B,0x80);//复位
	delay_ms(500);              //等待复位完成
	MPU6050_WriteReg(0x6B,0x00);//取消睡眠
	MPU6050_WriteReg(0x1B,0x08);//设置陀螺仪量程为500°/s
	MPU6050_WriteReg(0x1C,0x00);//设置加速度计量程
	
	MPU6050_WriteReg(0x1A,0x04);//配置滤波器参数
	MPU6050_WriteReg(0x19,0x00);//配置分频频率不分频，1000khz输出
	
	MPU6050_WriteReg(0x6B,0x02);//使用陀螺仪的晶振作为时钟
	MPU6050_WriteReg(0x6C,0x00);
}


void MPU_6050_GetData(struct MPU6050 *mpu6050) 
{
	uint8_t DataH,DataL;
	
	DataH = MPU6050_ReadReg(0x3B);
	DataL = MPU6050_ReadReg(0x3C);
	mpu6050->accx = (DataH<<8) + DataL;
	
	DataH = MPU6050_ReadReg(0x3D);
	DataL = MPU6050_ReadReg(0x3E);
	mpu6050->accy = (DataH<<8) + DataL;
	
	DataH = MPU6050_ReadReg(0x3F);
	DataL = MPU6050_ReadReg(0x40);
	mpu6050->accz = (DataH<<8) + DataL;
	
	DataH = MPU6050_ReadReg(0x41);
	DataL = MPU6050_ReadReg(0x42);
	mpu6050->temp = (DataH<<8) + DataL;
	mpu6050->temp = mpu6050->temp/340 + 36.53;
	
	DataH = MPU6050_ReadReg(0x43);
	DataL = MPU6050_ReadReg(0x44);
	mpu6050->gyrox = (DataH<<8) + DataL;
	
	DataH = MPU6050_ReadReg(0x45);
	DataL = MPU6050_ReadReg(0x46);
	mpu6050->gyroy = (DataH<<8) + DataL;
	
	DataH = MPU6050_ReadReg(0x47);
	DataL = MPU6050_ReadReg(0x48);
	mpu6050->gyroz = (DataH<<8) + DataL;
}
