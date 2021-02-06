/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "stm32f1xx_it.h"
#include "conf_gpio.h"

void Conf_TIM3_IC(void);
void Conf_NVIC(void);

int main(void)
{
  Conf_GPIO();
  Conf_GPIO_Remap();
  Conf_TIM3_IC();
  Conf_NVIC();

  while(1)
  {

  }

  return 0;
}

void Conf_TIM3_IC(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_ICInitTypeDef ic_struct;
  ic_struct.TIM_Channel = TIM_Channel_1;
  ic_struct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  ic_struct.TIM_ICPolarity = TIM_ICPolarity_Rising;
  ic_struct.TIM_ICFilter = 0;
  ic_struct.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM3, &ic_struct);

  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = TIM3_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 1;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);
}

// ----------------------------------------------------------------------------
