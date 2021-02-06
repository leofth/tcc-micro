#include "stm32f1xx_it.h"

void USART3_IRQHandler(void)
{
  uint16_t buffer;

  buffer = USART_ReceiveData(USART3);
  USART_SendData(USART3, buffer);

  if (buffer == 'l' || buffer == 'L')
  {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, 0);
  }
  else if (buffer == 'd' || buffer == 'D')
  {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, 1);
  }

  USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}
