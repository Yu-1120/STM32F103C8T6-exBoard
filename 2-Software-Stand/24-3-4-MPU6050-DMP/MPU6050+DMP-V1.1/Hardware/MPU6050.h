#ifndef __MPU6050_H
#define __MPU6050_H

struct MPU6050{
	short int accx;
	short int accy;
	short int accz;
	short int gyrox;
	short int gyroy;
	short int gyroz;
	short int temp;
};

void MPU6050_I2C_Init(void);
void MPU6050_W_SCL(uint8_t BitValue);
void MPU6050_W_SDA(uint8_t BitValue);
uint8_t MPU6050_R_SDA(void);
void MPU6050_I2C_S(void);
void MPU6050_I2C_P(void);
void MPU6050_I2C_SendByte(uint8_t byte);
uint8_t MPU6050_I2C_ReadByte(void);
void MPU6050_I2C_SendAck(uint8_t Ack);
uint8_t MPU6050_I2C_ReadAck(void);

void MPU_6050_Init(void);
uint8_t MPU6050_ReadReg(uint8_t Reg);
void MPU6050_WriteReg(uint8_t Reg, uint8_t data);
void MPU6050_Read_Temp(uint8_t *p);
void MPU_6050_GetData(struct MPU6050 *mpu6050);
uint8_t MPU6050_Burst_Read(uint8_t Addr, uint8_t reg, uint8_t len, uint8_t *buf);
uint8_t MPU6050_Burst_Write(uint8_t Addr, uint8_t reg, uint8_t len, uint8_t const *buf);


#endif
