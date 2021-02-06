#ifndef __stm32f1xx_it
#define __stm32f1xx_it

#include "stm32f10x_conf.h"
#include "lcd1602.h"

extern volatile float frequencia;

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);

#endif
