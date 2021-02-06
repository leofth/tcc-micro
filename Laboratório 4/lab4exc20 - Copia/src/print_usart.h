#ifndef PRINT_USART_H_
#define PRINT_USART_H_

#include <stm32f10x_conf.h>

void Print_USART3(char *string);
void Conf_USART3(void);

volatile uint32_t contador_ms = 0;

#endif
