/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include "stm32f10x_conf.h"
#include "stm32f1xx_it.h"
#include "conf_gpio.h"
#include "stdio.h"

void Conf_TIM2(void);
void Conf_TIM3(void);
void Conf_ADC(void);
void Conf_NVIC(void);
void Print_USART3(char *string);
void TIM3_Delay(uint32_t tempo);

typedef enum {
  wait_convertion=0,
  data_ready,
  print
} estado_adc;

volatile uint32_t contador_ms = 0;
volatile uint16_t ADC_DADO;
volatile estado_adc estado = wait_convertion;

#define a  0.000809
#define b -0.003196

int main(void)
{
  float tensao;
  char aux[50];

  Conf_GPIO();
  Conf_TIM2();
  Conf_TIM3();
  Conf_NVIC();
  Conf_ADC();

  while(1)
  {
    switch (estado)
    {
    case wait_convertion:
      if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
      {
        ADC_DADO = ADC_GetConversionValue (ADC1);
        estado = data_ready;
      }
      break;
    case data_ready:
      tensao = a * ADC_DADO + b;
      sprintf(aux, "tensao: %.2f\tADC_DADO: %d\r\n", tensao, ADC_DADO);
      estado = print;
      break;
    case print:
      Print_USART3(aux);
      TIM3_Delay(500000);
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

  ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_239Cycles5);
  ADC_Cmd(ADC1, ENABLE);

  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));

  //ADC_TempSensorVrefintCmd(ENABLE);
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

void Conf_TIM3(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseInitTypeDef timer3;
  timer3.TIM_Prescaler = 72-1;
  timer3.TIM_Period = 2-1;
  timer3.TIM_CounterMode =  TIM_CounterMode_Up;
  timer3.TIM_ClockDivision = 0;
  timer3.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &timer3);

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void TIM3_Delay(uint32_t tempo)
{
  TIM_Cmd(TIM3, ENABLE);

  while(tempo != contador_ms);

  contador_ms = 0;

  TIM_Cmd(TIM3, DISABLE);
}
// ----------------------------------------------------------------------------
