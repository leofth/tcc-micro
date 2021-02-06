#include "stm32f1xx_it.h"

void EXTI0_IRQHandler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_0,
	  GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)^1);

  EXTI_ClearITPendingBit(EXTI_Line0);
}
