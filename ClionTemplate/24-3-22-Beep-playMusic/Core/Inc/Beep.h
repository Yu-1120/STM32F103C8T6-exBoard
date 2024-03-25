#ifndef __BEEP_H
#define __BEEP_H

#include "Delay.h"
#define  BEEP_PIN  GPIO_Pin_11
#define  BEEP_GPIO  GPIOB

void BEEP_Init(void);
void BEEP_ON(void);
void BEEP_OFF(void);
void Sound(u16 frq);
void Sound2(u16 time);
void play_music(void);
void play_successful(void);
void play_failed(void);

#endif
