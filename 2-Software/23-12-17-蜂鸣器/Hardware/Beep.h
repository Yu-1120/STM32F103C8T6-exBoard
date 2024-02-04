#ifndef __BEEP_H
#define __BEEP_H


#define  BEEP_PIN  GPIO_Pin_11
#define  BEEP_GPIO  GPIOB

void BEEP_Init(void);
void BEEP_ON(void);
void BEEP_OFF(void);


#endif
