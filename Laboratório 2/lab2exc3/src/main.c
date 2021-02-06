/*
*
* data: sexta, 29 de maio de 2020
*
* Experimento 1.4: Cabo de guerra
*
* Neste experimento, deverá ser implementado o jogo de cabo de guerra usando
* push-buttons e a placa que contém 7 leds. O jogo deve ser feito para duas
* pessoas.
*
* Faça o jogo usando interrupções para a detecção de borda nos push-buttons.
*
*/

/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "stm32f1xx_it.h"
#include "conf_gpio.h"

#define ACESO     1
#define APAGADO   0
#define VANTAGEM  2

uint8_t pontos_1 = 0;
uint8_t pontos_2 = 0;

void Reseta_Jogo(void);
void Conf_EXTI(void);
void Conf_NVIC(void);

int main(void)
{

 Conf_GPIO();
 Conf_EXTI();
 Conf_NVIC();

 while(1)
 {
   if (cabo == VANTAGEM)
   {
     pontos_1++;
     cabo = 0;

     switch(pontos_1)
     {
       case 1:
         GPIO_WriteBit(GPIOB, GPIO_Pin_0, ACESO);
         break;
       case 2:
         GPIO_WriteBit(GPIOB, GPIO_Pin_1, ACESO);
         break;
       case 3:
         GPIO_WriteBit(GPIOB, GPIO_Pin_3, ACESO);
         break;
       case 4:
         GPIO_WriteBit(GPIOB, GPIO_Pin_4, ACESO);
         GPIO_WriteBit(GPIOB, GPIO_Pin_5, APAGADO);
         GPIO_WriteBit(GPIOB, GPIO_Pin_6, APAGADO);
         GPIO_WriteBit(GPIOB, GPIO_Pin_7, APAGADO);
         while(!GPIO_ReadInputDataBit(GPIOA, BOT_RESET));
         Reseta_Jogo();
         break;
       default:
         break;
     }
   }
   else if (cabo == -VANTAGEM)
   {
     pontos_2++;
     cabo = 0;

     switch(pontos_2)
     {
       case 1:
         GPIO_WriteBit(GPIOB, GPIO_Pin_7, ACESO);
         break;
       case 2:
         GPIO_WriteBit(GPIOB, GPIO_Pin_6, ACESO);
         break;
       case 3:
         GPIO_WriteBit(GPIOB, GPIO_Pin_5, ACESO);
         break;
       case 4:
         GPIO_WriteBit(GPIOB, GPIO_Pin_4, ACESO);
         GPIO_WriteBit(GPIOB, GPIO_Pin_0, APAGADO);
         GPIO_WriteBit(GPIOB, GPIO_Pin_1, APAGADO);
         GPIO_WriteBit(GPIOB, GPIO_Pin_3, APAGADO);
         while(!GPIO_ReadInputDataBit(GPIOA, BOT_RESET));
         Reseta_Jogo();
         break;
       default:
         break;
     }
   }
 }
}

void Conf_EXTI(void)
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);

 EXTI_InitTypeDef exti_struct;
 exti_struct.EXTI_Line = EXTI_Line0;
 exti_struct.EXTI_LineCmd = ENABLE;
 exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;
 exti_struct.EXTI_Trigger = EXTI_Trigger_Rising;
 EXTI_Init(&exti_struct);

 exti_struct.EXTI_Line = EXTI_Line1;
 EXTI_Init(&exti_struct);
}

void Conf_NVIC(void)
{
 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

 NVIC_InitTypeDef nvic_struct;
 nvic_struct.NVIC_IRQChannel = EXTI0_IRQn;
 nvic_struct.NVIC_IRQChannelCmd = ENABLE;
 nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
 nvic_struct.NVIC_IRQChannelSubPriority = 0;
 NVIC_Init(&nvic_struct);

 it.NVIC_IRQChannel = EXTI1_IRQn;
 NVIC_Init(&nvic_struct);
}

void Reseta_Jogo(void)
{
  GPIO_WriteBit(GPIOB, GPIO_Pin_0, APAGADO);
  GPIO_WriteBit(GPIOB, GPIO_Pin_1, APAGADO);
  GPIO_WriteBit(GPIOB, GPIO_Pin_3, APAGADO);
  GPIO_WriteBit(GPIOB, GPIO_Pin_4, APAGADO);
  GPIO_WriteBit(GPIOB, GPIO_Pin_5, APAGADO);
  GPIO_WriteBit(GPIOB, GPIO_Pin_6, APAGADO);
  GPIO_WriteBit(GPIOB, GPIO_Pin_7, APAGADO);

 pontos_1 = 0;
 pontos_2 = 0;
}

// ----------------------------------------------------------------------------
