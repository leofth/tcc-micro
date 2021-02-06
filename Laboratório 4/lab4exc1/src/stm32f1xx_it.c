#include "stm32f1xx_it.h"

void TIM2_IRQHandler(void)
{
	GPIO_WriteBit(GPIOC, GPIO_Pin_13,
	  GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)^1);

  TIM_ClearITPendingBit(TIM2_IT_UPDATE);
}
