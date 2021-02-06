/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "conf_gpio.h"
#include <stdio.h>

void Conf_USART3(void);

int main(void)
{
  Conf_GPIO();
  Conf_USART3();

  uint16_t buffer;

  while(1)
  {
    if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE))
    {
      buffer = USART_ReceiveData(USART3);
      USART_SendData(USART3, buffer);
    }
  }

  return 0;
}

void Conf_USART3(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  USART_InitTypeDef usart_struct;
  usart_struct.USART_BaudRate = 9600;
  usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_struct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  usart_struct.USART_Parity = USART_Parity_No;
  usart_struct.USART_StopBits = USART_StopBits_1;
  usart_struct.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART3, &usart_struct);

  USART_Cmd(USART3, ENABLE);
}

// ----------------------------------------------------------------------------
