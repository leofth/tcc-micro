/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "conf_gpio.h"
#include "stm32f1xx_it.h"
#include "lcd1602.h"

extern uint8_t print;

#define TIM2_PERIODO 0xFFFF
#define TIM2_PRESCALER 1

void Conf_TIM2(void);
void Conf_TIM2_IC(void);
void Conf_TIM3(void);
void Conf_NVIC(void);

int main(void)
{
  Conf_GPIO();
  Conf_GPIO_Remap();
  Conf_TIM2();
  Conf_TIM2_IC();
  Conf_TIM3();
  Conf_NVIC();

  TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

  LCD_Init();
  LCD_Start();
  LCD_Clear();

  char aux[50];

  while(1)
  {
    if (print == 1)
    {
      char *sinal = (frequencia < 0) ? "-" : "";
      float valor = (frequencia < 0) ? -frequencia : frequencia;

      int valor_int1 = valor;
      float valor_frac = valor - valor_int1;
      int valor_int2 = trunc(valor_frac * 10000);

      sprintf (aux, "f = %s%d.%d Hz\r\n", tmpSign, tmpInt1, tmpInt2);
      print = 0;
      LCD_Cursor(0, 0);
      LCD_Write(aux);
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

void Conf_TIM3(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseInitTypeDef timer3;
  timer3.TIM_Prescaler = 72-1;
  timer3.TIM_Period = 1000-1;
  timer3.TIM_CounterMode =  TIM_CounterMode_Up;
  timer3.TIM_ClockDivision = 0;
  timer3.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &timer3);

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef it;
  it.NVIC_IRQChannel = TIM2_IRQn;
  it.NVIC_IRQChannelCmd = ENABLE;
  it.NVIC_IRQChannelPreemptionPriority = 0;
  it.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&it);

  it.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_Init(&it);
}

// ----------------------------------------------------------------------------
