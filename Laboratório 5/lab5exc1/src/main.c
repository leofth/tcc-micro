/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "conf_gpio.h"
#include "stm32f1xx_it.h"

void Conf_TIM3(void);
void Conf_NVIC(void);
void TIM3_Delay(uint32_t tempo);

int main(void)
{
  Conf_GPIO();
  Conf_TIM3();
  Conf_NVIC();

  while(1)
  {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13,
      GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)^1);

    TIM3_Delay(500);
  }

  return 0;
}

void Conf_TIM3(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseInitTypeDef tim_struct;
  tim_struct.TIM_Prescaler = 72-1;
  tim_struct.TIM_Period = 1000-1;
  tim_struct.TIM_CounterMode =  TIM_CounterMode_Up;
  tim_struct.TIM_ClockDivision = 0;
  tim_struct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &tim_struct);

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = TIM3_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);
}

void TIM3_Delay(uint32_t tempo)
{
  TIM_Cmd(TIM3, ENABLE);

  while(tempo != contador_ms);

  contador_ms = 0;

  TIM_Cmd(TIM3, DISABLE);
}

// ----------------------------------------------------------------------------
