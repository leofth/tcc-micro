#include <conf_gpio.h>

void Conf_GPIO(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  //I2C1 - B6/SCLK B7/SDA
  GPIO_InitTypeDef gpio_structB;
  gpio_structB.GPIO_Mode = GPIO_Mode_AF_OD;
  gpio_structB.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  gpio_structB.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &gpio_structB);
}
