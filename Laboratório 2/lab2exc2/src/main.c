/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "stm32f1xx_it.h"
#include "conf_gpio.h"

void Conf_EXTI(void);
void Conf_NVIC(void);

int main(void)
{
  Conf_NVIC();
  Conf_EXTI();
  Conf_GPIO();

  while(1)
  {

  }

  return 0;
}

void Conf_EXTI(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);

  EXTI_InitTypeDef exti_struct;
  exti_struct.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2;
  exti_struct.EXTI_LineCmd = ENABLE;
  exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;
  exti_struct.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_Init(&exti_struct);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = EXTI0_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);

  nvic_struct.NVIC_IRQChannel = EXTI1_IRQn | EXTI2_IRQn;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_Init(&nvic_struct);
}

// ----------------------------------------------------------------------------
