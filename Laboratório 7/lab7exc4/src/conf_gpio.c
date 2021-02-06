#include "conf_gpio.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef gpio_structB;
  gpio_structB.GPIO_Mode = GPIO_Mode_AIN;
  gpio_structB.GPIO_Speed = GPIO_Speed_2MHz;
  gpio_structB.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOB, &gpio_structB);
}

void Conf_GPIO_Remap(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitTypeDef gpio_structB;
  gpio_structB.GPIO_Mode = GPIO_Mode_AF_PP;
  gpio_structB.GPIO_Pin = GPIO_Pin_10;
  gpio_structB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &gpio_structB);

  GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
}
