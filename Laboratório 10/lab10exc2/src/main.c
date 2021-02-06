/* ============================ CÃ“DIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

/* MULTIPLE BYTE: este modo faz com que, durante o write/read, o ADXL aponta para
 * o próximo endereço a cada ciclo de clock, parando apenas quando \CS for 1.
 *
 *
 */

#include <stm32f10x_conf.h>
#include <stm32f1xx_it.h>
#include "conf_gpio.h"
#include <stdio.h>

#define I2C_SlaveAddr 0xA0
#define I2C_Speed       100000

volatile uint32_t contador_ms = 0;
uint8_t ID;

void Conf_I2C1(void);
void TIM3_Delay(uint32_t tempo);
void Conf_USART3(void);
void Conf_NVIC(void);
void Conf_TIM3(void);
void Print_USART3(char *string);

void I2C_WriteBlock(uint8_t endereco, void *ptr, unsigned char tam);
void I2C_ReadBlock(uint8_t endereco, void *ptr, unsigned char tam);
void I2C_Write(uint8_t endereco, uint8_t comando, uint16_t escravo);
int8_t I2C_Read(uint8_t endereco, uint8_t escravo);

int main()
{
  char msg[30];
  double dado;

  Conf_GPIO();
  Conf_NVIC();
  Conf_USART3();
  Conf_TIM3();
  Conf_I2C1();

  char latitude[] = "-23.316862494560258";
  char b[80];
  int teste1 = 0;
  char teste2[] = "def";
  char teste3[] = "ghi";
  char teste4[] = "jkl";
  char teste5[] = "mno";
int a = 0;
  double d = -23.316862494560258;

  uint8_t aux;

////  I2C_WriteBlock(0x00, latitude, sizeof(latitude));  // data_format range= +- 4g
////  TIM3_Delay(1000);
////  I2C_ReadBlock(0x00, lat, sizeof(latitude));
//
//  uint16_t addr = 150;
////  uint8_t i = 0;
//
////  I2C_WriteBlock(addr, teste1, sizeof(teste1));
//  addr += sizeof(teste1);
////  I2C_WriteBlock(addr, teste2, sizeof(teste2));
//  addr += sizeof(teste2);
////  I2C_WriteBlock(addr, teste3, sizeof(teste3));
//  addr += sizeof(teste3);
////  I2C_WriteBlock(addr, teste4, sizeof(teste4));
//  addr += sizeof(teste4);
////  I2C_WriteBlock(addr, teste5, sizeof(teste5));
//  addr += sizeof(teste5);
//
////  for (int i = 0; i < 90; i++)
//    I2C_WriteBlock(0, &latitude, sizeof(latitude));
//
////  while(i != 256)
////  {
//    I2C_ReadBlock(0, b, sizeof(latitude));
//    sprintf(msg, "%d: %s\r\n", 0, b);
//    Print_USART3(msg);
////    i++;
////  }

  a = 0;
  int i = 0;

  while (i != 256)
  {
    I2C_Write(i, i+3, 0xA1);
    i++;
  }

  i = 0;

  while (i != 256)
  {
    aux = I2C_Read(i, 0xA0);
    sprintf(msg, "posicao da memoria %d: %d\r\n", i, aux);
    Print_USART3(msg);
    i++;
  }

  while(1)
  {
//    ID = I2C_Read(0x05, 0xA0);
//    sprintf(msg, "ID: %d\r\n", ID);
//    Print_USART3(msg);
  }

   return 0;
}

void I2C_WriteBlock(uint8_t endereco, void *ptr, unsigned char tam)
{
  unsigned char *data = ptr;

  while (tam--)
    I2C_Write(endereco++, *data++, 0xA0);
}

void I2C_ReadBlock(uint8_t endereco, void *ptr, unsigned char tam)
{
  unsigned char *data = ptr;

  while (tam--)
    *data++ = I2C_Read(endereco++, 0xA1);
}

void I2C_Write(uint8_t endereco, uint8_t comando, uint16_t escravo)
{
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  I2C_Send7bitAddress(I2C1, escravo, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  I2C_SendData(I2C1, endereco);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  I2C_SendData(I2C1, comando);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  I2C_GenerateSTOP(I2C1, ENABLE);
  TIM3_Delay(1000);
}

int8_t I2C_Read(uint8_t endereco, uint8_t escravo)
{
  int8_t dado;

  I2C_AcknowledgeConfig(I2C1, ENABLE);

  I2C_GenerateSTART(I2C1, ENABLE);

  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  I2C_Send7bitAddress(I2C1, escravo, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  I2C_SendData(I2C1, endereco);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  I2C_Send7bitAddress(I2C1, escravo, I2C_Direction_Receiver);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
  dado = I2C_ReceiveData(I2C1);

  I2C_AcknowledgeConfig(I2C1, DISABLE);

  I2C_GenerateSTOP(I2C1, ENABLE);
  TIM3_Delay(1000);

  return dado;
}

void Conf_I2C1(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  I2C_InitTypeDef i2c_struct;
  i2c_struct.I2C_Ack = I2C_Ack_Enable;
  i2c_struct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  i2c_struct.I2C_ClockSpeed = I2C_Speed;
  i2c_struct.I2C_DutyCycle = I2C_DutyCycle_2;
  i2c_struct.I2C_Mode = I2C_Mode_I2C;
  i2c_struct.I2C_OwnAddress1 = 0x00;

  I2C_Init(I2C1, &i2c_struct);

  I2C_Cmd(I2C1, ENABLE);
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
}

void Conf_TIM3(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  TIM_TimeBaseInitTypeDef tim3_struct;
  tim3_struct.TIM_Prescaler = 72-1;
  tim3_struct.TIM_Period = 2-1;
  tim3_struct.TIM_CounterMode =  TIM_CounterMode_Up;
  tim3_struct.TIM_ClockDivision = 0;
  tim3_struct.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM3, &tim3_struct);

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void Conf_NVIC(void)
{
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = TIM3_IRQn;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvic_struct);
}

void TIM3_Delay(uint32_t tempo)
{
  TIM_Cmd(TIM3, ENABLE);

  while(tempo != contador_ms);

  contador_ms = 0;

  TIM_Cmd(TIM3, DISABLE);
}

void Print_USART3(char *string)
{
  while(*string != 0)
  {
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    USART_SendData(USART3, *(string++));
  }
}

// ----------------------------------------------------------------------------
