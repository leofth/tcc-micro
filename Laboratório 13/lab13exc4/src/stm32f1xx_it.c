#include "stm32f1xx_it.h"

typedef enum
{
  received = 0,
  process,
  store,
  read,
  wait
} estado;

extern estado estado_GPS;

void USART3_IRQHandler(void)
{
  estado_GPS = received;

  USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}

void TIM3_IRQHandler(void)
{
  contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

