#include <conf_gpio.h>

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  //USART2
  GPIO_InitTypeDef gpio_structA;
  gpio_structA.GPIO_Mode = GPIO_Mode_AF_PP;
  gpio_structA.GPIO_Pin = GPIO_Pin_2;
  gpio_structA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &gpio_structA);

  gpio_structA.GPIO_Pin = GPIO_Pin_3;
  gpio_structA.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &gpio_structA);

  //USART3
  GPIO_InitTypeDef gpio_structB;
  gpio_structB.GPIO_Mode = GPIO_Mode_AF_PP;
  gpio_structB.GPIO_Pin = GPIO_Pin_10;
  gpio_structB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &gpio_structB);

  gpio_structB.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  gpio_structB.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOB, &gpio_structB);
}
