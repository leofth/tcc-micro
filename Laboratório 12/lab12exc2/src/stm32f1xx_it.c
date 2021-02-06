#include <stm32f1xx_it.h>

uint8_t varredura[4] = {0b11010000, 0b10110000, 0b01110000, 0b11100000};
uint8_t coluna = 0;
char teclado[4][4] = {{'1', '2', '3', 'A'},
                      {'4', '5', '6', 'B'},
                      {'7', '8', '9', 'C'},
                      {'*', '0', '#', 'D'}};
char msg[50];
char pwd[6][7];
pwd[0] = "123ABC";
pwd[1] = "214212";
pwd[2] = "ABC123";
pwd[3] = "ABCABC";
pwd[4] = "123456";
pwd[5] = "111111";
char aux[7];
uint8_t index = 0;

void TIM2_IRQHandler(void)
{
  GPIO_Write(GPIOA, (GPIO_ReadOutputData(GPIOA) & 0xFF0F) | varredura[coluna++]);

  if (coluna == 4)
    coluna = 0;

  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void EXTI0_IRQHandler(void)
{
  sprintf(msg, "%c\r\n", teclado[0][coluna]);
  Print_USART3(msg);
  aux[index] = teclado[0][coluna];
  index++;
  if (index == 5)
  {
    index = 0;
    if (aux == pwd)
    {
      index = 1;
    }
  }
  EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
  sprintf(msg, "%c\r\n", teclado[1][coluna]);
  Print_USART3(msg);
  aux[index] = teclado[1][coluna];
  index++;
  if (index == 5)
  {
    index = 0;
    if (aux == pwd)
    {
      index = 1;
    }
  }
  EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
  sprintf(msg, "%c\r\n", teclado[2][coluna]);
  Print_USART3(msg);
  aux[index] = teclado[2][coluna];
  index++;
  if (index == 5)
  {
    index = 0;
    if (aux == pwd)
    {
      index = 1;
    }
  }
  EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(void)
{
  sprintf(msg, "%c\r\n", teclado[3][coluna]);
  Print_USART3(msg);
  aux[index] = teclado[3][coluna];
  index++;
  if (index == 5)
  {
    index = 0;
    if (aux == pwd)
    {
      index = 1;
    }
  }
  EXTI_ClearITPendingBit(EXTI_Line3);
}
