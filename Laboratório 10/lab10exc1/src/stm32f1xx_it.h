#ifndef __stm32f1xx_it
#define __stm32f1xx_it

#include "stm32f10x_conf.h"

extern volatile uint32_t contador_ms;

void TIM3_IRQHandler(void);

#endif
