#ifndef __stm32f1xx_it
#define __stm32f1xx_it

#include "stm32f10x_conf.h"

char msg[50];
uint16_t contador = 0;

void TIM3_IRQHandler(void);

#endif
