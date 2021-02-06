// ----------------------------------------------------------------------------
/* ============================ CÓDIGO EXEMPLO ============================= */

#include <stdio.h>
#include <stm32f10x_conf.h>

void LED_Delay(void);
void Conf_GPIO(void);

int main(void)
{
  Conf_GPIO();

  while (1)
  {
    GPIO_WriteBit(GPIOC, GPIO_Pin_13, GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)^1);
    LED_Delay();
  }

  return 0;
}

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef portC;
  portC.GPIO_Mode = GPIO_Mode_Out_PP;
  portC.GPIO_Pin = GPIO_Pin_13;
  portC.GPIO_Speed = GPIO_Speed_10MHz;

  GPIO_Init(GPIOC, &portC);
}

void LED_delay(void)
{
  volatile unsigned int i;

  for (i = 0; i < 2000000; i++);
}

// ----------------------------------------------------------------------------
