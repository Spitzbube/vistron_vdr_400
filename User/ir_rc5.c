

#include "main.h"


#define RC5_NUM_BITS 13  /*Excluding the Start Bit*/


uint8_t bData_2000013c = 0xff;

uint8_t bData_200008dc;
volatile uint8_t bData_200008dd;
uint8_t bData_200008de;
uint16_t wData_200008e0;
uint16_t wData_200008e2;
uint16_t wData_200008e4;
uint16_t wData_200008e6;
uint16_t wData_200008e8;
uint16_t wData_200008ea;
static uint8_t rc5_bFrameComplete;
static uint16_t arBitBuffer[RC5_NUM_BITS];
uint8_t bData_20000908;


static void ir_rc5_start(void)
{
   HAL_TIM_Base_DeInit(&htim2);

   htim2.Instance = TIM2;
   htim2.Init.Prescaler = 71;
   htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim2.Init.Period = 65535;
   htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
   htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

   if (0 != HAL_TIM_Base_Init(&htim2))
   {
      Error_Handler();
   }

   HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
   HAL_TIM_Base_Stop_IT(&htim2);
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
   HAL_NVIC_EnableIRQ(EXTI3_IRQn);
   TIM2->ARR = 65535;
}


void ir_rc5_get_data(RC5_Data* pAppData)
{
   uint32_t i;
   uint8_t r5 = rc5_bFrameComplete;

   if (pAppData->bData_1 != 0)
   {
      if (r5 != 1)
      {
         pAppData->bData_2 = 0;
         pAppData->bData_3 = 0;
      }
      else
      {
         pAppData->rc_code = 0;
         pAppData->bData_2 = 0;
         pAppData->bData_3 = 0;
         TIM2->SR = 0;

         pAppData->bData_3 = ((arBitBuffer[0]) & 1);

         uint8_t bAddress = 0;
         for (i = 1; i < 6; i++)
         {
            bAddress <<= 1;
            if (arBitBuffer[i] & 1)
            {
               bAddress |= 1;
            }
         }

         uint8_t bCommand = 0;
         for (  ; i < 12; i++)
         {
            bCommand <<= 1;
            if (arBitBuffer[i] & 1)
            {
               bCommand |= 1;
            }
         }

         pAppData->rc_code = bCommand;

         if (bData_200008de == 0)
         {
            pAppData->rc_code |= 0x40;
         }

         if (bAddress != 0x16)
         {
            pAppData->rc_code = 0xff;
            rc5_bFrameComplete = 0;

            ir_rc5_start();
         }
         else
         {
            if (pAppData->bData_3 == bData_2000013c)
            {
               if (bData_20000908 != 0)
               {
                  pAppData->bData_2 = 1;

                  if (bData_20000908 != 2)
                  {
                     bData_20000908++;
                     pAppData->rc_code = 0xff;
                     rc5_bFrameComplete = 0;

                     ir_rc5_start();
                  }
                  else
                  {
                     bData_20000908 = 1;
                     bData_2000013c = pAppData->bData_3;
                     return;
                  }
               }
               else
               {
                  pAppData->rc_code = 0xff;

                  rc5_bFrameComplete = 0;

                  ir_rc5_start();

                  bData_20000908++;
                  return;
               }
            }
            else
            {
               pAppData->bData_2 = 0;
               bData_20000908 = 0;
               bData_2000013c = pAppData->bData_3;
               return;
            }
         }
      }
   } //if (pAppData->bData_1 != 0)
   else
   {
      if (r5 == 1)
      {
         pAppData->rc_code = 0xff;
         rc5_bFrameComplete = 0;

         ir_rc5_start();

         pAppData->bData_1 = 1;
      }
   }
}


void ir_rc5_init(RC5_Data* pAppData)
{
	volatile uint32_t sp4;

	uint32_t r6 = ((RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos);
	uint32_t r0 = HAL_RCC_GetPCLK1Freq();
	if (r6 < 4)
	{
		r0 = r0 / 72;
	}
	else
	{
		r0 = r0 * 2 / 72;
	}
	sp4 = r0 / 1000;
	wData_200008e8 = sp4 * 1778 / 1000;
	sp4;
	wData_200008e6 = sp4 * 720 / 1000;
	wData_200008e4 = sp4 * 1110 / 1000;
	wData_200008e2 = sp4 * 1440 / 1000;
	wData_200008e0 = sp4 * 2220 / 1000;
	wData_200008ea = (wData_200008e8 * 3) / 4;

	ir_rc5_start();

	pAppData->rc_code = 0xff;
	pAppData->bData_1 = 1;
	pAppData->bData_2 = 0;
	pAppData->bData_3 = 1;
}


void App_TIM2_IRQHandler(void)
{
   static uint8_t rc5_bBitCount = 0;

   arBitBuffer[rc5_bBitCount] = (GPIOD->IDR & IR_RX_Pin)? 1: 0;
   rc5_bBitCount++;

   if (bData_200008dc == 0)
   {
      TIM2->ARR = wData_200008e8;
      bData_200008dc = 1;
   }

   if (rc5_bBitCount == RC5_NUM_BITS)
   {
      rc5_bBitCount = 0;
      bData_200008dc = 0;
      rc5_bFrameComplete = 1;

      HAL_TIM_Base_Stop_IT(&htim2);
      HAL_NVIC_DisableIRQ(TIM2_IRQn);
   }

   HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);

   __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
}


void App_EXTI0_IRQHandler(void)
{
   volatile uint16_t sp6;

   if ((EXTI->PR & EXTI_PR_PR3) == EXTI_PR_PR3)
   {
      bData_200008dd++;
      if (bData_200008dd == 1)
      {
         TIM2->CNT = 0;
         HAL_TIM_Base_Start(&htim2);
      }
      else if (bData_200008dd == 2)
      {
         HAL_TIM_Base_Stop(&htim2);

         sp6 = TIM2->CNT;
         TIM2->CNT = 0;

         if ((wData_200008e6 > sp6) || (wData_200008e4 < sp6))
         {
            if ((wData_200008e2 < sp6) && (wData_200008e0 > sp6))
            {
               HAL_NVIC_DisableIRQ(EXTI3_IRQn);

               __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);

               HAL_TIM_Base_Start_IT(&htim2);
               HAL_NVIC_EnableIRQ(TIM2_IRQn);

               TIM2->ARR = wData_200008ea;
               bData_200008de = 0;
               bData_200008dd = 0;
            }
            else
            {
               TIM2->CNT = 0;
               bData_200008dd = 0;
            }
         }
      }
      else if (bData_200008dd == 3)
      {
         HAL_NVIC_DisableIRQ(EXTI3_IRQn);

         __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);

         HAL_TIM_Base_Start_IT(&htim2);
         HAL_NVIC_EnableIRQ(TIM2_IRQn);

         TIM2->ARR = wData_200008ea;
         bData_200008de = 1;
         bData_200008dd = 0;
      }
   }
}

