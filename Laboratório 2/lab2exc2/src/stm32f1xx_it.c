#include "stm32f1xx_it.h"
#include <stdio.h>

void EXTI0_IRQHandler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_0,
	  GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0)^1);

  EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_1,
    GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1)^1);

  EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_2,
    GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2)^1);

  EXTI_ClearITPendingBit(EXTI_Line2);
}
