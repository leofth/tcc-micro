#include "conf_gpio.h"

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef gpio_structA;
  gpio_structA.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio_structA.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
                    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  gpio_structA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &gpio_structA);
}
