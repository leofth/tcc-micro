#include <conf_gpio.h>

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitTypeDef portaA;
  portaA.GPIO_Mode = GPIO_Mode_IPU;
  portaA.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  portaA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &portaA);

  portaA.GPIO_Mode = GPIO_Mode_Out_OD;
  portaA.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  portaA.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &portaA);

  GPIO_InitTypeDef portaB;
  portaB.GPIO_Mode = GPIO_Mode_AF_PP;
  portaB.GPIO_Pin = GPIO_Pin_10;
  portaB.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &portaB);

  portaB.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  portaB.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOB, &portaB);
}
