#include "stm32f1xx_it.h"
#include "print_usart.h"
#include <stdio.h>

//char msg[50];
//uint16_t contador = 0;

void TIM3_IRQHandler(void)
{
  GPIO_WriteBit(GPIOC, GPIO_Pin_13,
  GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)^1);

  sprintf(msg, "Quantidade de bordas: %d\n", contador++);

  Print_USART3(msg);

  TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}
