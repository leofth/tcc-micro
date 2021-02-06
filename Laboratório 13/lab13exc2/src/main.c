/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include "stm32f10x_conf.h"
#include "stm32f1xx_it.h"
#include "conf_gpio.h"
#include "stdio.h"
#include <string.h>

void Conf_NVIC(void);
void Conf_USART3(void);
void Print_USART3(char *string);
int EncontraNMEA(char str[][80]);
int SeparaNMEA(char *str, char m[][80]);

typedef enum
{
  received = 0,
  process,
  send,
  wait
} estado;

estado estado_GPS;

int main(void)
{
  char aux[50];

  Conf_GPIO();
  Conf_NVIC();
  Conf_USART3();

  char buffer[9][80];
  char pos_gps[50];
  uint16_t i = 0, j = 0;
  char gps[15][80];
  int index = 0;

  while (1)
  {
    switch (estado_GPS)
    {
      case received:
        buffer[i][j] = USART_ReceiveData(USART3);
//        USART_SendData(USART3, buffer[i][j]);
        j++;
        estado_GPS = wait; //espera até obter toda a string nmea

        if (buffer[i][j - 1] == '\n')
        {
          i++;
          j = 0;

          if (i == 9)
          {
            i = 0;
            estado_GPS = process; //nmea obtido
          }
        }
        break;
      case process:
        index = EncontraNMEA(buffer);
        SeparaNMEA(buffer[index], gps);
        estado_GPS = send;
        break;
      case send:
        sprintf(pos_gps, "Latitude: %s, %s\n\rLongitude: %s, %s\n\r", gps[2], gps[3], gps[4], gps[5]);
        Print_USART3(pos_gps);
        estado_GPS = wait;
        break;
      case wait:
      default:
        break;
    }
  }

  return 0;
}

int EncontraNMEA(char str[][80])
{
  int i = 0;

  while(i < 10)
  {
    if (str[i][3] == 'G' && str[i][4] == 'G' && str[i][5] == 'A')
      return i;
    else
      i++;
  }

  return 0;
}

int SeparaNMEA(char *str, char m[][80])
{
  int i = 0, j = 0;
  char *nmea;
  char c[2] = ",";
-
  nmea = strtok(str, c);

  while(1)
  {
    while(*nmea != '\0')
    {
      m[i][j] = *nmea;
      if (*nmea == '\r')
      {
        m[i][j] = '\0';
        return 0;
      }
      nmea++;
      j++;
    }
    m[i][j] = '\0';
    j = 0;
    i++;
    nmea = strtok(NULL, c);
  }
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = USART3_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);
}

void Print_USART3(char *string)
{
  while(*string != 0)
  {
    while(!USART_GetFlagStatus(USART3, USART_FLAG_TXE));
    USART_SendData(USART3, *string++);
  }
}

void Conf_USART3(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  USART_InitTypeDef usart_struct;
  usart_struct.USART_BaudRate = 9600;
  usart_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  usart_struct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  usart_struct.USART_Parity = USART_Parity_No;
  usart_struct.USART_StopBits = USART_StopBits_1;
  usart_struct.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART3, &usart_struct);

  USART_Cmd(USART3, ENABLE);

  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}

// ----------------------------------------------------------------------------
