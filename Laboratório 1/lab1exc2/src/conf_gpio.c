#include "conf_gpio.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef portaA;
  portaA.GPIO_Mode = GPIO_Mode_Out_PP;
  portaA.GPIO_Pin = GPIO_Pin_0;
  portaA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &portaA);

  GPIO_InitTypeDef portaB;
  portaB.GPIO_Mode = GPIO_Mode_IPD;
  portaB.GPIO_Pin = GPIO_Pin_0;
  portaB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &portaB);
}
