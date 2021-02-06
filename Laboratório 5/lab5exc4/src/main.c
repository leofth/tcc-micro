/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "conf_gpio.h"
#include "stm32f1xx_it.h"

extern uint8_t print;

#define TIM2_PERIODO 0xFFFF
#define TIM2_PRESCALER 1

void Conf_TIM2(void);
void Conf_TIM2_IC(void);
//void Conf_TIM3(void);
void Conf_NVIC(void);
void Conf_USART3(void);
void Print_USART3(char *string);

int main(void)
{
  Conf_GPIO();
  Conf_TIM2();
  Conf_TIM2_IC();
  Conf_NVIC();
  Conf_USART3();

  TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

  char aux[50];

//  char *tmpSign = (frequencia < 0) ? "-" : "";
//  float tmpVal = (frequencia < 0) ? -frequencia : frequencia;
//
//  int tmpInt1 = tmpVal;                  // Get the integer (678).
//  float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
//  int tmpInt2 = trunc(tmpFrac * 10000);

  while(1)
  {
    if (print == 1)
    {
      char *tmpSign = (frequencia < 0) ? "-" : "";
      float tmpVal = (frequencia < 0) ? -frequencia : frequencia;

      int tmpInt1 = tmpVal;                  // Get the integer (678).
      float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
      int tmpInt2 = trunc(tmpFrac * 10000);

      sprintf (aux, "f = %s%d.%d Hz\r\n", tmpSign, tmpInt1, tmpInt2);
      Print_USART3(aux);
      print = 0;
    }
  }

  return 0;
}

void Conf_TIM2(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef timer2;
  timer2.TIM_Prescaler = TIM2_PRESCALER-1;
  timer2.TIM_Period = TIM2_PERIODO-1;
  timer2.TIM_CounterMode =  TIM_CounterMode_Up;
  timer2.TIM_ClockDivision = 0;
  timer2.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &timer2);
}

void Conf_TIM2_IC(void)
{
  TIM_ICInitTypeDef ic;
  ic.TIM_Channel = TIM_Channel_3;
  ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  ic.TIM_ICPolarity = TIM_ICPolarity_Rising;
  ic.TIM_ICFilter = 0;
  ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM2, &ic);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef it;
  it.NVIC_IRQChannel = TIM2_IRQn;
  it.NVIC_IRQChannelCmd = ENABLE;
  it.NVIC_IRQChannelPreemptionPriority = 0;
  it.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&it);
}

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
