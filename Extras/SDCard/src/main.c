/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include <stm32f1xx_it.h>
#include <stdio.h>
#include "conf_gpio.h"
#include "delay.h"
#include "print_usart.h"

#define BMP280Write     0xEC
#define BMP280Read      0xED

int main()
{
  char msg[50];
  uint8_t ID = 0;

  Conf_GPIO();
  Conf_USART3();
  Conf_TIM3();
  Conf_SPI1_Master();

  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 1);

  while(1)
  {
    BMP280_Read(0xD0, &ID, 1);
    sprintf(msg, "ID: %d\r\n", ID);
    Print_USART3(msg);
    TIM3_Delay(500);
  }

   return 0;
}

// ----------------------------------------------------------------------------
