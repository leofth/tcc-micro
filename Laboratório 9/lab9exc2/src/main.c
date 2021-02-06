/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include <stm32f1xx_it.h>
#include "conf_gpio.h"
#include "print_usart.h"
#include "delay.h"
#include <stdio.h>
#include <math.h>

#define BMP280Write     0xEC
#define BMP280Read      0xED

signed long temperature_raw, pressure_raw;
unsigned short dig_T1, dig_P1;
signed short dig_T2, dig_T3, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
float temperature, pressure, altitude;

uint8_t ID = 0;

void Conf_SPI1_Master(void);

void BMP280_get_calib_values(void);
void BMP280_calc_values(void);
void BMP280_Init(void);
void BMP280_Write(uint8_t endereco, uint8_t dado);
void BMP280_Read(uint8_t endereco, uint8_t *buffer, uint8_t tam);
uint8_t BMP280_Transfer(uint8_t outByte);

int main()
{
  char msg[50];

  Conf_GPIO();
  Conf_USART3();
  Conf_TIM3();
  Conf_SPI1_Master();

  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 1);

  BMP280_Init();

  while(1)
  {
    BMP280_Read(0xD0, &ID, 1);
    BMP280_calc_values();
    sprintf(msg, "P: %.2f\t T: %.2f\t A: %.2f\r\nID: %d\r\n", pressure/100, temperature, altitude, ID);
    Print_USART3(msg);
    TIM3_Delay(500);
  }

   return 0;
}

uint8_t BMP280_Transfer(uint8_t comando)
{
  while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
  SPI_I2S_SendData(SPI1, comando);
  while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
  return SPI_I2S_ReceiveData(SPI1);
}

void BMP280_Write(uint8_t endereco, uint8_t dado)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 0);

  BMP280_Transfer(endereco);

  BMP280_Transfer(dado);

  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 1);
}

void BMP280_Read(uint8_t endereco, uint8_t *buffer, uint8_t tam)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 0);

  BMP280_Transfer(endereco);

  for (int i = 0; i < tam; i++)
  {
    *buffer = BMP280_Transfer(0x00);
    buffer++;
    TIM3_Delay(1);
  }

  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 1);
}

void BMP280_Init(void)
{
  BMP280_Write(0x75, 0x90);
  BMP280_Write(0x74, 0x57);

  BMP280_get_calib_values();
}

void BMP280_get_calib_values(void)
{
  uint8_t rx_buff[24], starting_address=0x88;

  BMP280_Read(starting_address, rx_buff, 24);

  dig_T1=(rx_buff[0])+(rx_buff[1]<<8);
  dig_T2=(rx_buff[2])+(rx_buff[3]<<8);
  dig_T3=(rx_buff[4])+(rx_buff[5]<<8);
  dig_P1=(rx_buff[6])+(rx_buff[7]<<8);
  dig_P2=(rx_buff[8])+(rx_buff[9]<<8);
  dig_P3=(rx_buff[10])+(rx_buff[11]<<8);
  dig_P4=(rx_buff[12])+(rx_buff[13]<<8);
  dig_P5=(rx_buff[14])+(rx_buff[15]<<8);
  dig_P6=(rx_buff[16])+(rx_buff[17]<<8);
  dig_P7=(rx_buff[18])+(rx_buff[19]<<8);
  dig_P8=(rx_buff[20])+(rx_buff[21]<<8);
  dig_P9=(rx_buff[22])+(rx_buff[23]<<8);
}

void BMP280_calc_values(void)
{
  uint8_t status, rx_buff[6], starting_address=0xF7;

  do
  {
    BMP280_Read(0xF3, &status, 1);
  } while(((status&0b00001000)==8)||((status&0b00000001)==1));

  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 0);

  BMP280_Transfer(starting_address);

  for(int i = 0; i < 6; i++)
  {
    rx_buff[i] = BMP280_Transfer(0x00);
  }

  GPIO_WriteBit(GPIOA, GPIO_Pin_3, 1);

  volatile uint32_t temp[3];
  temp[2]=rx_buff[3];
  temp[1]=rx_buff[4];
  temp[0]=rx_buff[5];
  temperature_raw=(temp[2]<<12)+(temp[1]<<4)+(temp[0]>>4);

  temp[2]=rx_buff[0];
  temp[1]=rx_buff[1];
  temp[0]=rx_buff[2];
  pressure_raw=(temp[2]<<12)+(temp[1]<<4)+(temp[0]>>4);

  double var1, var2;
  var1=(((double)temperature_raw)/16384.0-((double)dig_T1)/1024.0)*((double)dig_T2);
  var2=((((double)temperature_raw)/131072.0-((double)dig_T1)/8192.0)*(((double)temperature_raw)/131072.0-((double)dig_T1)/8192.0))*((double)dig_T3);
  double t_fine = (int32_t)(var1+var2);
  volatile float T = (var1+var2)/5120.0;

  var1=((double)t_fine/2.0)-64000.0;
  var2=var1*var1*((double)dig_P6)/32768.0;
  var2=var2+var1*((double)dig_P5)*2.0;
  var2=(var2/4.0)+(((double)dig_P4)*65536.0);
  var1=(((double)dig_P3)*var1*var1/524288.0+((double)dig_P2)*var1)/524288.0;
  var1=(1.0+var1/32768.0)*((double)dig_P1);

  volatile double p=1048576.0-(double)pressure_raw;
  p=(p-(var2/4096.0))*6250.0/var1;
  var1=((double)dig_P9)*p*p/2147483648.0;
  var2=p*((double)dig_P8)/32768.0;
  p=p+(var1+var2+((double)dig_P7))/16.0;

  temperature=T;
  pressure=p;
  altitude=44330.0f*(1-powf(pressure/101325.0f,1.0f/5.255f));
  //altitude=((powf(101325.0/pressure, 1/5.257f)-1)*(temperature+273.15f))/0.0065f;
}

void Conf_SPI1_Master(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  SPI_InitTypeDef SPI_InitDef;
  SPI_InitDef.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitDef.SPI_Mode = SPI_Mode_Master;
  SPI_InitDef.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitDef.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitDef.SPI_CPOL = SPI_CPOL_High;
  SPI_InitDef.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitDef.SPI_NSS = SPI_NSS_Soft;
  SPI_InitDef.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
  SPI_InitDef.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitDef);

  SPI_Cmd(SPI1, ENABLE);
}

// ----------------------------------------------------------------------------
