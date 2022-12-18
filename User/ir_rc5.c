

#include "main.h"

/*
 * ST Application Note: http://www.st.com/internet/com/TECHNICAL_RESOURCES/TECHNICAL_LITERATURE/APPLICATION_NOTE/CD00267896.pdf
 * Source Code: http://dekar.wc3edit.net/st%20website/an3174.zip
 */

#define RC5_TIM_PRESCALER 71
#define RC5_NUM_BITS 13  /*Excluding the Start Bit*/

#define   NOMINAL_HALF_BIT_TIME_US   889  /* Nominal half bit time in µs */
#define   MIN_HALF_BIT_TIME_US       720/*640*/  /* Minimum half bit time in µs */
#define   MAX_HALF_BIT_TIME_US       1110/*1140*/ /* Maximum half bit time in µs */

#define   NOMINAL_FULL_BIT_TIME_US   1778 /* Nominal Full bit time in µs */
#define   MIN_FULL_BIT_TIME_US       1440/*1340*/ /* Minimum Full bit time in µs */
#define   MAX_FULL_BIT_TIME_US       2220 /* Maximum Full bit time in µs */


static uint8_t FieldBit;
static uint16_t FullBitDurationCount_Max;
static uint16_t FullBitDurationCount_Min;
static uint16_t HalfBitDurationCount_Max;
static uint16_t HalfBitDurationCount_Min;
static uint16_t NominalHalfBitDurationCount;
static uint16_t NominalBitDurationCount;
static uint16_t NominalBitDurationCount_3div4;
static uint8_t RC5_FrameReceived;
static uint16_t RC5_data[RC5_NUM_BITS];
uint8_t bData_20000908;


static void ir_rc5_start(void)
{
   HAL_TIM_Base_DeInit(&htim2);

   htim2.Instance = TIM2;
   htim2.Init.Prescaler = RC5_TIM_PRESCALER;
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
   static uint8_t bOldToggleBit = 0xff;
   uint32_t i;
   uint8_t r5 = RC5_FrameReceived;

   if (pAppData->bData_1 != 0)
   {
      if (r5 != 1)
      {
         pAppData->bData_2 = 0;
         pAppData->ToggleBit = 0;
      }
      else
      {
         pAppData->Command = 0;
         pAppData->bData_2 = 0;
         pAppData->ToggleBit = 0;
         TIM2->SR = 0;

         pAppData->ToggleBit = ((RC5_data[0]) & 1);

         uint8_t bAddress = 0;
         for (i = 1; i < 6; i++)
         {
            bAddress <<= 1;
            if (RC5_data[i] & 1)
            {
               bAddress |= 1;
            }
         }

         uint8_t bCommand = 0;
         for (  ; i < 12; i++)
         {
            bCommand <<= 1;
            if (RC5_data[i] & 1)
            {
               bCommand |= 1;
            }
         }

         pAppData->Command = bCommand;

         /* Set the 6th bit of the command regarding of the filed bit value */
         if (FieldBit == 0) /* logic 0 = command from 64 to 127 */
         {
            pAppData->Command |= 0x40;
         }

         if (bAddress != 0x16)
         {
            pAppData->Command = 0xff;
            RC5_FrameReceived = 0;

            ir_rc5_start();
         }
         else
         {
            if (pAppData->ToggleBit == bOldToggleBit)
            {
               if (bData_20000908 != 0)
               {
                  pAppData->bData_2 = 1;

                  if (bData_20000908 != 2)
                  {
                     bData_20000908++;
                     pAppData->Command = 0xff;
                     RC5_FrameReceived = 0;

                     ir_rc5_start();
                  }
                  else
                  {
                     bData_20000908 = 1;
                     bOldToggleBit = pAppData->ToggleBit;
                     return;
                  }
               }
               else
               {
                  pAppData->Command = 0xff;

                  RC5_FrameReceived = 0;

                  ir_rc5_start();

                  bData_20000908++;
                  return;
               }
            }
            else
            {
               pAppData->bData_2 = 0;
               bData_20000908 = 0;
               bOldToggleBit = pAppData->ToggleBit;
               return;
            }
         }
      }
   } //if (pAppData->bData_1 != 0)
   else
   {
      if (r5 == 1)
      {
         pAppData->Command = 0xff;
         RC5_FrameReceived = 0;

         ir_rc5_start();

         pAppData->bData_1 = 1;
      }
   }
}


void ir_rc5_init(RC5_Data* pAppData)
{
	volatile uint32_t RC5_TIM_CLKValuekHz;

	uint32_t apbprescaler = ((RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos);
	uint32_t apbfrequency = HAL_RCC_GetPCLK1Freq();
	if (apbprescaler < 4)
	{
		apbfrequency = apbfrequency / (RC5_TIM_PRESCALER + 1);
	}
	else
	{
		apbfrequency = apbfrequency * 2 / (RC5_TIM_PRESCALER + 1);
	}
	RC5_TIM_CLKValuekHz = apbfrequency / 1000;

	NominalBitDurationCount = RC5_TIM_CLKValuekHz * NOMINAL_FULL_BIT_TIME_US / 1000;
	NominalHalfBitDurationCount = RC5_TIM_CLKValuekHz * NOMINAL_HALF_BIT_TIME_US / 1000;
	HalfBitDurationCount_Min = RC5_TIM_CLKValuekHz * MIN_HALF_BIT_TIME_US / 1000; // 889 - 720 = 169
	HalfBitDurationCount_Max = RC5_TIM_CLKValuekHz * MAX_HALF_BIT_TIME_US / 1000; // 1110 - 889 = 221
	FullBitDurationCount_Min = RC5_TIM_CLKValuekHz * MIN_FULL_BIT_TIME_US / 1000; // 1778 - 1440 = 338
	FullBitDurationCount_Max = RC5_TIM_CLKValuekHz * MAX_FULL_BIT_TIME_US / 1000; // 2220 - 1778 = 442
	NominalBitDurationCount_3div4 = (NominalBitDurationCount * 3) / 4;

	ir_rc5_start();

	pAppData->Command = 0xff;
	pAppData->bData_1 = 1;
	pAppData->bData_2 = 0;
	pAppData->ToggleBit = 1;
}


void App_TIM2_IRQHandler(void)
{
   static uint8_t Bit4_HasBeen_Sampled = 0;
   static uint8_t RC5_Indexdata = 0;

   RC5_data[RC5_Indexdata] = (GPIOD->IDR & IR_RX_Pin)? 1: 0;
   RC5_Indexdata++;

   if (Bit4_HasBeen_Sampled == 0)
   {
      TIM2->ARR = NominalBitDurationCount;
      Bit4_HasBeen_Sampled = 1;
   }

   if (RC5_Indexdata == RC5_NUM_BITS)
   {
      RC5_Indexdata = 0;
      Bit4_HasBeen_Sampled = 0;
      RC5_FrameReceived = 1;

      HAL_TIM_Base_Stop_IT(&htim2);
      HAL_NVIC_DisableIRQ(TIM2_IRQn);
   }

   HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);

   __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
}


void App_EXTI0_IRQHandler(void)
{
   static volatile uint8_t EdgesNumber = 0;
   volatile uint16_t LowDuration;

   if ((EXTI->PR & EXTI_PR_PR3) == EXTI_PR_PR3)
   {
      EdgesNumber++;
      if (EdgesNumber == 1)
      {
    	  /*
    	   * First EXTI interrupt event (1): the TIMx counter is initialized and enabled.
    	   */
         TIM2->CNT = 0;
         HAL_TIM_Base_Start(&htim2);
      }
      else if (EdgesNumber == 2)
      {
    	  /*
    	   * Second EXTI interrupt event (2): the TIMx counter is disabled, read and then initialized.
The value read from the counter gives the measured duration. The 3rd execution of the
EXTI interrupt depends on the measured duration:
– If the duration is within the tolerance range of one half bit time, the EXTI is not
disabled and the EXTI interrupt occurs for the 3rd time, which enables TIMx. TIMx
then starts sampling the RC5 data. In this case the Field bit is recognized as a
logical 1.
– If the duration is within the tolerance range of one bit time, the EXTI is then
disabled at this moment and the TIMx update event interrupt as well as the TIMx
counter are enabled to start sampling the RC5 data. In this case the Field bit is
recognized as a logical 0. If the duration seems to be a glitch, the system is
initialized for the next RC5 frame.
    	   */

         HAL_TIM_Base_Stop(&htim2);

         LowDuration = TIM2->CNT;
         TIM2->CNT = 0;

         if ((HalfBitDurationCount_Min > LowDuration) || (HalfBitDurationCount_Max < LowDuration))
         {
            if ((FullBitDurationCount_Min < LowDuration) && (FullBitDurationCount_Max > LowDuration))
            {
               HAL_NVIC_DisableIRQ(EXTI3_IRQn);

               __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);

               HAL_TIM_Base_Start_IT(&htim2);
               HAL_NVIC_EnableIRQ(TIM2_IRQn);

               TIM2->ARR = NominalBitDurationCount_3div4;
               FieldBit = 0;
               EdgesNumber = 0;
            }
            else
            {
               TIM2->CNT = 0;
               EdgesNumber = 0;
            }
         }
      }
      else if (EdgesNumber == 3)
      {
    	  /*
    	   * Third EXTI interrupt event (3): this interrupt occurrence depends on the duration of the
first low duration, see (2). When the interrupt occurs, TIMx is enabled and starts
sampling the RC5 data.
    	   */
         HAL_NVIC_DisableIRQ(EXTI3_IRQn);

         __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);

         HAL_TIM_Base_Start_IT(&htim2);
         HAL_NVIC_EnableIRQ(TIM2_IRQn);

         TIM2->ARR = NominalBitDurationCount_3div4;
         FieldBit = 1;
         EdgesNumber = 0;
      }
   }
}

