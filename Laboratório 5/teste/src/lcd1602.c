#include "lcd1602.h"
#include "delay.h"

volatile uint32_t contador_ms = 0;

void LCD_SendByte(int data, int rs)
{
  GPIO_WriteBit(GPIOA, GPIO_Pin_0, rs);
  GPIO_WriteBit(GPIOA, GPIO_Pin_1, 0);

  GPIO_WriteBit(GPIOA, GPIO_Pin_7, ((data>>3) & 0x01));
  GPIO_WriteBit(GPIOA, GPIO_Pin_6, ((data>>2) & 0x01));
  GPIO_WriteBit(GPIOA, GPIO_Pin_5, ((data>>1) & 0x01));
  GPIO_WriteBit(GPIOA, GPIO_Pin_4, ((data>>0) & 0x01));

  GPIO_WriteBit(GPIOA, GPIO_Pin_2, 1);
  TIM_Delay(20);
  GPIO_WriteBit(GPIOA, GPIO_Pin_2, 0);
  TIM_Delay(20);
}

void LCD_SendCmd(int cmd)
{
    int datatosend;

    datatosend = ((cmd>>4)&0x0F);
    LCD_SendByte(datatosend,0); 

    datatosend = ((cmd)&0x0F);
    LCD_SendByte(datatosend, 0);
}

void LCD_SendData(int data)
{
    int datatosend;

    datatosend = ((data>>4)&0x0F);
    LCD_SendByte(datatosend, 1);

    datatosend = ((data)&0x0F);
    LCD_SendByte(datatosend, 1);
}

void LCD_Cursor(int row, int col)
{
  switch (row)
  {
    case 0:
        col |= 0x80;
        break;
    case 1:
        col |= 0xC0;
        break;
//    case 2:
//        col |= 0x94;
//        break;
//    case 3:
//        col |= 0xD4;
//        break;
    default:
        break;
  }

  LCD_SendCmd(col);
}

void LCD_Init(void)
{
  //16x4
  // 4 bit initialisation
  TIM_Delay(50);
  LCD_SendCmd(0x30); // Function set
  TIM_Delay(5);
  LCD_SendCmd(0x20); // Function set
  LCD_SendCmd(0x80); // Function set
  TIM_Delay(5);
  LCD_SendCmd(0x20); // Function set
  LCD_SendCmd(0x80); // Function set
  TIM_Delay(5);
  LCD_SendCmd(0x00); // Display ON/OFF control
  LCD_SendCmd(0x00); // Display ON/OFF control
  TIM_Delay(5);
  LCD_SendCmd(0x00); // Display clear
  LCD_SendCmd(0x10); // Display clear
  TIM_Delay(5);
  LCD_SendCmd(0x00); // Entry mode set
  LCD_SendCmd(0x60); // Entry mode set
  TIM_Delay(5);

  //16x2
//  TIM_Delay(50);
//  LCD_SendCmd(0x30); // Function set
//  TIM_Delay(5);
//  LCD_SendCmd(0x30); // Function set
//  TIM_Delay(1);
//  LCD_SendCmd(0x30); // Function set
//  TIM_Delay(1);
//  LCD_SendCmd(0x3C); // Function set
//  LCD_SendCmd(0x08); // Function set
//  LCD_SendCmd(0x01); // Function set
//  LCD_SendCmd(0x04); // Function set

//   TIM_Delay(40);
//   LCD_SendCmd(0x30);
//   TIM_Delay(5);
//   LCD_SendCmd(0x30);
//   TIM_Delay(1);
//   LCD_SendCmd(0x30);
//   TIM_Delay(1);
//   LCD_SendCmd(0x20);  // 4bit mode
//   TIM_Delay(1);
//
//  // // display initialisation
////   LCD_SendCmd(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
////   TIM_Delay(5);
//   LCD_SendCmd(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0
//   TIM_Delay(5);
//   LCD_SendCmd(0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
//   TIM_Delay(5);
//   LCD_SendCmd(0x01); // clear display
//   TIM_Delay(5);
//   LCD_SendCmd(0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
//   TIM_Delay(5);
//   LCD_SendCmd(0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
//   TIM_Delay(5);
}

void TIM_Delay(uint32_t tempo)
{
  TIM_Cmd(TIM3, ENABLE);

  while(tempo != contador_ms);

  contador_ms = 0;
  
  TIM_Cmd(TIM3, DISABLE);
}

void LCD_Write(char* c)
{
  while (*c)
  {
    LCD_SendData(*c++);
  }
}

void LCD_Clear(void)
{
 LCD_SendCmd(0x01); 
}

void LCD_Start(void)
{
  int row = 0, col = 0;

  for (int i = 0; i < 32; i++)
  {
    LCD_Cursor(row, col);

    col++;

    if (col > 15)
    {
      row++;
      col = 0;
    }
    if (row > 1)
      row=0;
  }
}
