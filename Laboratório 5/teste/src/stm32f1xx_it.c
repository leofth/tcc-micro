#include <stm32f1xx_it.h>

void TIM3_IRQHandler(void)
{
  contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
