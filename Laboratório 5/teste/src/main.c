/*
*
* data: 20 de junho de 2020
*
* Experimento x: xxxx xxxx
*
* Descrição do experimento
*
*/

/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include <stdio.h>
#include "conf_gpio.h"
#include "stm32f1xx_it.h"
#include "lcd1602.h"
#include "delay.h"

int main(void)
{
  Conf_GPIO();
  Conf_TIM3();

  LCD_Init();
  LCD_Start();
  LCD_Clear();

  char teste[20] = "Leonardo";
  // int i = 0;
//  char aux[20];

  while(1)
  {
    LCD_Cursor(0, 0);
    //sprintf(aux, "bordas = %d", );
    LCD_Write(teste);
  }

  return 0;
}
// ----------------------------------------------------------------------------
