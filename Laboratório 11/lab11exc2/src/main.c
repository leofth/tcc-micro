/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>

#define ON  0
#define OFF 1

int main (void)
{
  RCC->APB2ENR = 0x00000010;
  RCC->APB1ENR = 0x00000002;

  GPIOC->CRL = 0x00000000;
  GPIOC->CRH = 0x00200000;

  TIM3->CR1 = 0x00000081; //1000 0001
  TIM3->ARR = 4999;
  TIM3->PSC = 7199;
//  TIM3->RCR = 0;

  uint8_t estado = ON;

  while (1)
  {
    if ((TIM3->SR & 0x0001) == SET)
    {
      if (estado == ON)
      {
        GPIOC->BSRR = 0x00002000;
        estado = OFF;
      }
      else
      {
        GPIOC->BRR = 0x00002000;
        estado = ON;
      }
//      GPIOC->BSRR = 0x20000000;
      TIM3->SR = 0;
    }
  }
  return 0;
}

// ----------------------------------------------------------------------------
