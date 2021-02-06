/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include <stm32f1xx_it.h>
#include "conf_gpio.h"
#include "print_usart.h"
#include "delay.h"
//#include "eeprom.h"

void Conf_EXTI(void);
void Conf_NVIC(void);
void Conf_TIM2(void);

int main()
{
  Conf_GPIO();
  Conf_NVIC();
  Conf_EXTI();
  Conf_TIM2();
  Conf_USART3();
//  Conf_I2C1();

  while(1)
  {

  }

   return 0;
}

void Conf_EXTI(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);

  EXTI_InitTypeDef exti_struct;
  exti_struct.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3;
  exti_struct.EXTI_LineCmd = ENABLE;
  exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;
  exti_struct.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&exti_struct);
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
  nvic_struct.NVIC_IRQChannel = EXTI0_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);

  nvic_struct.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_Init(&nvic_struct);

  nvic_struct.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_Init(&nvic_struct);

  nvic_struct.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_Init(&nvic_struct);

  nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_Init(&nvic_struct);
}
// ----------------------------------------------------------------------------
