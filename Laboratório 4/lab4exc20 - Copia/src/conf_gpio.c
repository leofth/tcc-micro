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
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitTypeDef gpio_structC;
  gpio_structC.GPIO_Mode = GPIO_Mode_IPD;
  gpio_structC.GPIO_Pin = GPIO_Pin_1;
  gpio_structC.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &gpio_structC);

  GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
}
