#include "stm32f10x.h"                  // Device header
#include "pid.h"
#include "DHT11.h"
u8 buf[5];
PID pid;
void PID1_Init(void)
{
    pid.SetSpeed=0.0;     //�趨ֵ
    pid.ActualSpeed=0.0;  //ʵ��ֵ
    pid.err=0.0;          //ƫ��ֵ
    pid.err_last=0.0;     //������һ��ƫ��ֵ
    pid.OUT=0.0;          //�����ѹֵ(����ִ�����ı���
    pid.integral=0.0;     //�������ֵ
    pid.Kp=0.2;
    pid.Ki=0.015;
    pid.Kd=0.2;
}

float PID1_realize(float speed)
{
	 
     pid.SetSpeed=speed;
     pid.err=pid.SetSpeed-pid.ActualSpeed;
     pid.integral+=pid.err;
     pid.OUT=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
     pid.err_last=pid.err;
     pid.ActualSpeed=pid.OUT*1.0;
   return pid.ActualSpeed;
}
