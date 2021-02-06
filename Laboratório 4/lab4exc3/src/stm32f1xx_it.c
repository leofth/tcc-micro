#include "stm32f1xx_it.h"

uint32_t miliseg = 0;
volatile uint8_t indice = 0;
//uint16_t digitos[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uint8_t digitos[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // cátodo comum

void TIM2_IRQHandler(void)
{
  if (miliseg == 60)
  {
    indice++;
    miliseg = 0;
    if (10 == indice)
    {
      indice = 0;
    }
  }
  else
    miliseg++;

  GPIO_Write(GPIOA, digitos[indice]);

  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
