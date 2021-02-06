/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "stm32f1xx_it.h"
#include "conf_gpio.h"

void Conf_TIM2(void);
void Conf_NVIC(void);

int main(void)
{
  Conf_GPIO();
  Conf_TIM2();
  Conf_NVIC();

  GPIOA->ODR = 0;

  while(1)
  {

  }

  return 0;
}

void Conf_TIM2(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef tim_struct;
  tim_struct.TIM_Prescaler = 7200-1;
  tim_struct.TIM_Period = 1000-1;
  tim_struct.TIM_CounterMode =  TIM_CounterMode_Up;
  tim_struct.TIM_ClockDivision = 0;
  tim_struct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &tim_struct);

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);
}

// ----------------------------------------------------------------------------
