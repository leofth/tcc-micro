#include "eeprom.h"

volatile uint32_t contador_ms = 0;

void EEPROM_WriteBlock(uint8_t endereco, void *ptr, unsigned char tam)
{
  unsigned char *data = ptr;

  while (tam--)
    EEPROM_Write(endereco++, *data++, 0xA0);
}

void EEPROM_ReadBlock(uint8_t endereco, void *ptr, unsigned char tam)
{
  unsigned char *data = ptr;

  while (tam--)
    *data++ = EEPROM_Read(endereco++, 0xA1);
}

void EEPROM_Write(uint8_t endereco, uint8_t comando, uint16_t escravo)
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

int8_t EEPROM_Read(uint8_t endereco, uint8_t escravo)
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
  i2c_struct.I2C_ClockSpeed = 100000;
  i2c_struct.I2C_DutyCycle = I2C_DutyCycle_2;
  i2c_struct.I2C_Mode = I2C_Mode_I2C;
  i2c_struct.I2C_OwnAddress1 = 0x00;

  I2C_Init(I2C1, &i2c_struct);

  I2C_Cmd(I2C1, ENABLE);
}

void TIM3_Delay(uint32_t tempo)
{
  TIM_Cmd(TIM3, ENABLE);

  while(tempo != contador_ms);

  contador_ms = 0;

  TIM_Cmd(TIM3, DISABLE);
}
// ----------------------------------------------------------------------------
