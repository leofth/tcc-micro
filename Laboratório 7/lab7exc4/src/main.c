/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <conf_gpio.h>
#include "stm32f10x_conf.h"
#include "stm32f1xx_it.h"

void Conf_TIM2(void);
void Conf_TIM2_OC(void);
void Conf_TIM4(void);
void Conf_ADC(void);
void Conf_NVIC(void);

typedef enum {
  wait_convertion=0,
  data_ready,
  print_and_pwm
}tipo_exemplo_adc;

volatile uint16_t ADC_DADO;
volatile tipo_exemplo_adc estado_exemplo_adc = wait_convertion;

int main(void)
{
  Conf_GPIO();
  Conf_GPIO_Remap();
  Conf_TIM2();
  Conf_TIM2_OC();
  Conf_NVIC();
  Conf_TIM4();
  Conf_ADC();

  char aux[20];

  while(1)
  {
    switch (estado_exemplo_adc)
    {
    case wait_convertion:
      if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
      {
        ADC_DADO = ADC_GetConversionValue (ADC1);
        estado_exemplo_adc = data_ready;
      }
      break;
    case data_ready:
      if (ADC_DADO < 900)
        ADC_DADO = 900;

      sprintf(aux, "ADC: %d\r\n", ADC_DADO);
      TIM_SetCompare3(TIM2, ADC_DADO);
      estado_exemplo_adc = print_and_pwm;
      break;
    case print_and_pwm:
      estado_exemplo_adc = wait_convertion;
      break;
    default:
      break;
    }
  }

  return 0;
}

void Conf_ADC(void)
{
  RCC_ADCCLKConfig (RCC_PCLK2_Div6);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_InitTypeDef adc_struct;
  adc_struct.ADC_ContinuousConvMode = DISABLE;
  adc_struct.ADC_DataAlign = ADC_DataAlign_Right;
  adc_struct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  adc_struct.ADC_Mode = ADC_Mode_Independent;
  adc_struct.ADC_NbrOfChannel = 1;
  adc_struct.ADC_ScanConvMode = DISABLE;
  ADC_Init(ADC1, &adc_struct);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5);
  ADC_Cmd (ADC1,ENABLE);

  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
}

void Conf_TIM2_OC(void)
{
  TIM_OCInitTypeDef oc_struct;
  oc_struct.TIM_OCMode = TIM_OCMode_PWM1;
  oc_struct.TIM_OCPolarity = TIM_OCPolarity_High;
  oc_struct.TIM_OutputState = TIM_OutputState_Enable;
  oc_struct.TIM_Pulse = 0;
  TIM_OC3Init(TIM2, &oc_struct);
}

void Conf_TIM2(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef tim2_struct;
  tim2_struct.TIM_Prescaler = 35-1;
  tim2_struct.TIM_Period = 40960-1;
  tim2_struct.TIM_CounterMode =  TIM_CounterMode_Up;
  tim2_struct.TIM_ClockDivision = 0;
  tim2_struct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &tim2_struct);

  TIM_Cmd(TIM2, ENABLE);
}

void Conf_TIM4(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  TIM_TimeBaseInitTypeDef tim4_struct;
  tim4_struct.TIM_Prescaler = 7200-1;
  tim4_struct.TIM_Period = 100-1;
  tim4_struct.TIM_CounterMode =  TIM_CounterMode_Up;
  tim4_struct.TIM_ClockDivision = 0;
  tim4_struct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM4, &tim4_struct);

  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = TIM4_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);
}

// ----------------------------------------------------------------------------
