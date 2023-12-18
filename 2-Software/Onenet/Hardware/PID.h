#ifndef __PID_H
#define __PID_H	 

typedef struct
{
    float SetSpeed;       //�����趨ֵ
    float ActualSpeed;    //����ʵ��ֵ
    float err;            //����ƫ��ֵ
    float err_last;       //������һ��ƫ��ֵ
    float Kp,Ki,Kd;       //������������֡�΢��ϵ��
    float OUT;        //�����ѹֵ(����ִ�����ı���)
    float integral;       //�������ֵ
}PID;

extern PID pid;

void PID1_Init(void);
float PID1_realize(float speed);
		 				    
#endif
