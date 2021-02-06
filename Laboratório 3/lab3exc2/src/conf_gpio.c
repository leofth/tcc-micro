#include "conf_gpio.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef gpio_structB;
  gpio_structB.GPIO_Mode = GPIO_Mode_AF_PP;
  gpio_structB.GPIO_Pin = GPIO_Pin_10;
  gpio_structB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &gpio_structB);

  gpio_structB.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  gpio_structB.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOB, &gpio_structB);

  GPIO_InitTypeDef gpio_structC;
  gpio_structC.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio_structC.GPIO_Pin = GPIO_Pin_13;
  gpio_structC.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &gpio_structC);
}
