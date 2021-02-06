#include "stm32f1xx_it.h"

void TIM4_IRQHandler(void)
{
  ADC_Cmd(ADC1, ENABLE);

  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
