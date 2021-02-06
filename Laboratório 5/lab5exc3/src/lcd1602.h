#ifndef __lcd1602
#define __lcd1602

#include <stm32f10x_conf.h>

#define DATA_PORT   GPIOA
#define D0_PIN      GPIO_Pin_0
#define D1_PIN      GPIO_Pin_1
#define D2_PIN      GPIO_Pin_2
#define D3_PIN      GPIO_Pin_3
#define D4_PIN      GPIO_Pin_4
#define D5_PIN      GPIO_Pin_5
#define D6_PIN      GPIO_Pin_6
#define D7_PIN      GPIO_Pin_7

#define CMD_PORT    GPIOB
#define RS_PIN      GPIO_Pin_12
#define RW_PIN      GPIO_Pin_13
#define EN_PIN      GPIO_Pin_14

extern volatile uint32_t contador_ms;

void LCD_SendByte(int data, int rs);
void LCD_SendData(int data);
void LCD_SendCmd(int cmd);
void LCD_Cursor(int row, int col);
void TIM_Delay(uint32_t tempo);
void LCD_Init(void);
void LCD_Write(char* c);
void LCD_Clear(void);
void LCD_Start(void);

#endif
