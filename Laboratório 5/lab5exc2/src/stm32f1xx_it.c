#include <stm32f1xx_it.h>
#include "lcd1602.h"

void TIM3_IRQHandler(void)
{
  contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
