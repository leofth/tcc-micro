#include "print_usart.h"

void Print_USART3(char *string)
{
  while(*string != 0)
  {
    while(!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
    USART_SendData(USART3, *string++);
  }
}

void Conf_USART3(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  USART_InitTypeDef usart_struct;
  usart_struct.USART_BaudRate = 9600;
  usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_struct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  usart_struct.USART_Parity = USART_Parity_No;
  usart_struct.USART_StopBits = USART_StopBits_1;
  usart_struct.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART3, &usart_struct);

  USART_Cmd(USART3, ENABLE);

  GPIO_InitTypeDef gpio_structB;
  gpio_structB.GPIO_Mode = GPIO_Mode_AF_PP;
  gpio_structB.GPIO_Pin = GPIO_Pin_10;
  gpio_structB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &gpio_structB);

  gpio_structB.GPIO_Mode = GPIO_Mode_IPU;
  gpio_structB.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOB, &gpio_structB);
}
