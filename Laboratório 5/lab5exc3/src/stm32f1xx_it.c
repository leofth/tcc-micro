#include <stm32f1xx_it.h>

volatile float frequencia = 0;
uint16_t captura, borda_atu, borda_ant = 0;
uint8_t print = 0;

void TIM2_IRQHandler(void)
{
  borda_atu = TIM_GetCapture3(TIM2);

  if (borda_atu > borda_ant)
    captura = borda_atu - borda_ant;
  else
    captura = 65536 - borda_ant + borda_atu;

  borda_ant = borda_atu;
  frequencia = (72000000.0)/captura;
  print = 1;

  TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
}

void TIM3_IRQHandler(void)
{
  contador_ms++;

  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
