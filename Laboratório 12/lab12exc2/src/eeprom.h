#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdio.h>
#include "stm32f10x_conf.h"

void EEPROM_WriteBlock(uint8_t endereco, void *ptr, unsigned char tam);
void EEPROM_ReadBlock(uint8_t endereco, void *ptr, unsigned char tam);
void EEPROM_Write(uint8_t endereco, uint8_t comando, uint16_t escravo);
int8_t EEPROM_Read(uint8_t endereco, uint8_t escravo);
void Conf_I2C1(void);
void TIM3_Delay(uint32_t tempo);

#endif
