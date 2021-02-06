#include "conf_gpio.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef gpio_structC;
  gpio_structC.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio_structC.GPIO_Pin = GPIO_Pin_13;
  gpio_structC.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &gpio_structC);
}

void Conf_GPIO_Remap(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitTypeDef gpio_structB;
  gpio_structB.GPIO_Mode = GPIO_Mode_IPD;
  gpio_structB.GPIO_Pin = GPIO_Pin_5;
  gpio_structB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &gpio_structB);

  GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
}
