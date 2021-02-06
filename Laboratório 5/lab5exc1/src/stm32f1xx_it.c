#include "stm32f1xx_it.h"
#include <stdio.h>

volatile uint32_t contador_ms = 0;

void TIM3_IRQHandler(void)
{
	contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

