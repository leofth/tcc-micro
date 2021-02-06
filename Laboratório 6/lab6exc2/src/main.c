/*
*
* data: 20 de junho de 2020
*
* Experimento x: xxxx xxxx
*
* Descrição do experimento
*
*/

/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include "stm32f10x_conf.h"
#include "stm32f1xx_it.h"
#include "conf_gpio.h"
#include "delay.h"
#include "print_usart.h"
#include "stdio.h"
#include <float.h>

void Conf_TIM2(void);
void Conf_ADC(void);
void Conf_NVIC(void);

typedef enum {
  wait_convertion=0,
  data_ready,
  print
} estado_adc;

volatile uint16_t ADC_DADO;
volatile estado_adc estado = wait_convertion;

#define V_25 1.43
#define Avg_Slope 0.0043

int main(void)
{
  char aux[50];
  float temperatura;

  Conf_GPIO();
  Conf_TIM2();
  Conf_TIM3();
  Conf_NVIC();
  Conf_ADC();
  Conf_USART3();


  char aux1[20];
  char aux2[20];

  while(1)
  {
    switch (estado)
    {
    case wait_convertion:
      if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {//se acabou a conversão
        ADC_DADO = ADC_GetConversionValue (ADC1);//atribui o valor convertido do ADC1 ao ADC_DADO
        estado = data_ready;
      }
      break;
    case data_ready:
      temperatura = (V_25 - ADC_DADO*3.3/4095)/Avg_Slope + 25;
      sprintf(aux1, "temperatura: %.2f", temperatura);
      sprintf(aux2, "ADC: %d", ADC_DADO);
      estado = print;
      break;
    case print:
      temperatura = (V_25 - ADC_DADO*3.3/4095)/Avg_Slope + 25;
      Print_USART3(aux1);
      TIM3_Delay(1);
      estado = wait_convertion;
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

  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);

  ADC_TempSensorVrefintCmd(ENABLE);

  ADC_Cmd (ADC1,ENABLE);

  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
}

void Conf_TIM2(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef tim_struct;
  tim_struct.TIM_Prescaler = 7200-1;
  tim_struct.TIM_Period = 10000-1;
  tim_struct.TIM_CounterMode =  TIM_CounterMode_Up;
  tim_struct.TIM_ClockDivision = 0;
  tim_struct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &tim_struct);

  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
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

  nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_Init(&nvic_struct);
}

// ----------------------------------------------------------------------------
