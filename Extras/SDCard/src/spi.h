/*
 * spi.h
 *
 *  Created on: 18 de jan de 2021
 *      Author: leohi
 */

#ifndef SPI_H_
#define SPI_H_

#include <stm32f10x_conf.h>
#include "delay.h"

uint8_t SPI_Transfer(uint8_t comando);
void SPI_Write(uint8_t endereco, uint8_t dado);
void SPI_Read(uint8_t endereco, uint8_t *buffer, uint8_t tam);


#endif /* SPI_H_ */
