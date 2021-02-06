/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include <stm32f1xx_it.h>
#include "conf_gpio.h"
#include <stdio.h>

void Conf_USART3(void);
void Conf_NVIC(void);

int main(void)
{
  Conf_GPIO();
  Conf_NVIC();
  Conf_USART3();

  while(1)
  {

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
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = USART3_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);
}

// ----------------------------------------------------------------------------
