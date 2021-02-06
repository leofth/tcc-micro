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

#define I2C_SlaveAddr 0xA0
#define I2C_Speed       100000

volatile uint32_t contador_ms = 0;

void Conf_I2C1(void);
void TIM3_Delay(uint32_t tempo);
void Conf_NVIC(void);
void Conf_TIM3(void);

void I2C_Write(uint8_t endereco, uint8_t comando, uint16_t escravo);

int main()
{
  Conf_GPIO();
  Conf_NVIC();
  Conf_TIM3();
  Conf_I2C1();

  I2C_Write(0x05, 123, 0xA1);

  while(1)
  {

  }

   return 0;
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

// ----------------------------------------------------------------------------
