#include "spi.h"

uint8_t SPI_Transfer(uint8_t comando)
{
  while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
  SPI_I2S_SendData(SPI1, comando);
  while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
  return SPI_I2S_ReceiveData(SPI1);
}

void SPI_Write(uint8_t endereco, uint8_t dado)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 0);

  SPI_Transfer(endereco);

  SPI_Transfer(dado);

  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 1);
}

void SPI_Read(uint8_t endereco, uint8_t *buffer, uint8_t tam)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 0);

  SPI_Transfer(endereco);

  for (int i = 0; i < tam; i++)
  {
    *buffer = SPI_Transfer(0x00);
    buffer++;
    TIM3_Delay(1);
  }

  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 1);
}

void Conf_SPI1_Master(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  SPI_InitTypeDef spi_struct;
  spi_struct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  spi_struct.SPI_Mode = SPI_Mode_Master;
  spi_struct.SPI_DataSize = SPI_DataSize_8b;
  spi_struct.SPI_FirstBit = SPI_FirstBit_MSB;
  spi_struct.SPI_CPOL = SPI_CPOL_High;
  spi_struct.SPI_CPHA = SPI_CPHA_2Edge;
  spi_struct.SPI_NSS = SPI_NSS_Soft;
  spi_struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
  spi_struct.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &spi_struct);

  SPI_Cmd(SPI1, ENABLE);
}
