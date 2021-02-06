/* ============================ CÓDIGO EXEMPLO ============================= */
// ----------------------------------------------------------------------------

#include <stm32f10x_conf.h>
#include "conf_gpio.h"

void Conf_EXTI(void);

int main(void)
{
  Conf_EXTI();
  Conf_GPIO();

  while(1)
  {
    if (EXTI_GetFlagStatus(EXTI_Line0))
    {
      GPIO_WriteBit(GPIOA, GPIO_Pin_0,
        GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)^1);

      EXTI_ClearFlag(EXTI_Line0);
    }
  }

  return 0;
}

void Conf_EXTI(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

  EXTI_InitTypeDef portaB;
  portaB.EXTI_Line = EXTI_Line0;
  portaB.EXTI_LineCmd = ENABLE;
  portaB.EXTI_Mode = EXTI_Mode_Interrupt;
  portaB.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_Init(&portaB);
}

// ----------------------------------------------------------------------------
