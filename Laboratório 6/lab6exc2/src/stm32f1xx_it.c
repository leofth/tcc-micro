#include "stm32f1xx_it.h"
#include <stdio.h>

extern volatile uint32_t contador_ms;

void TIM2_IRQHandler(void)
{
  ADC_Cmd(ADC1, ENABLE);
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void TIM3_IRQHandler(void)
{
  contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

