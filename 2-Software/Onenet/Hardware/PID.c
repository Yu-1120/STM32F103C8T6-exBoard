#include "stm32f10x.h"                  // Device header
#include "pid.h"
#include "DHT11.h"
u8 buf[5];
PID pid;
void PID1_Init(void)
{
    pid.SetSpeed=0.0;     //设定值
    pid.ActualSpeed=0.0;  //实际值
    pid.err=0.0;          //偏差值
    pid.err_last=0.0;     //定义上一个偏差值
    pid.OUT=0.0;          //定义电压值(控制执行器的变量
    pid.integral=0.0;     //定义积分值
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
