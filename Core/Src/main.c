/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "../../User/func_8001ae8.h"
#include <stdlib.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

SRAM_HandleTypeDef hsram1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_FSMC_Init(void);
/* USER CODE BEGIN PFP */

extern int sub_800b270(void);
extern int sub_800a9a8(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* 800c7e0 - todo */
void sub_800c7e0(uint16_t a)
{
   TIM_HandleTypeDef htim;

   htim.Instance = TIM6;

   HAL_TIM_Base_Start_IT(&htim);

   while (a--)
   {
      while (!__HAL_TIM_GET_FLAG(&htim, TIM_FLAG_UPDATE)) // ((htim.Instance->SR & TIM_FLAG_UPDATE) != TIM_FLAG_UPDATE)
      {
         /* wait */
      }

      __HAL_TIM_CLEAR_FLAG(&htim, TIM_FLAG_UPDATE); //htim.Instance->SR = ~TIM_FLAG_UPDATE;
   }

   HAL_TIM_Base_Stop_IT(&htim);
}


/* 800c88c - todo */
uint16_t sub_800c88c(uint8_t r7_4[], uint16_t r7_2)
{
   uint16_t r7_e = 0;
   uint8_t r7_d = 0;

   while (r7_e++ < r7_2)
   {
      //loc_800c8a2
      if (r7_4[r7_e] == 0)
      {
         return r7_e;
      }
      //loc_800c8b2
      if (r7_4[r7_e] == ' ')
      {
         r7_d++;
         if (r7_d > 1)
         {
        	 return r7_e - 1;
         }
      }
      else
      {
         //loc_800c8d2
         r7_d = 0;
      }
   }

   return r7_e - 1;
}


int8_t Data_20000a5a; //20000a5a
int8_t Data_20000a5c; //20000a5c

struct
{
   int fill_0[32]; //0
   uint8_t bData_0x80; //0x80

} Data_20000a78; //20000a78

int Data_20000af8; //20000af8
struct
{
   int fill_0[32]; //0
   uint8_t bData_0x80; //0x80

} Data_20000afc;


/* 800dd74 - todo */
void RTC_IRQHandler(void)
{
   wData_20000a56 |= 0x10;

   sub_801050c(&hrtc);
}


/* 800dd98 - todo */
void RTC_Alarm_IRQHandler(void)
{
   wData_20000a56 |= 0x08;

   HAL_RTC_AlarmIRQHandler(&hrtc);
}


/* 8001802 - todo */
uint8_t sub_8001802(uint16_t a, uint16_t b)
{
   if ((a > 7) && (a < 45) && (b > 195) && (b < 233))
   {
      //blue
      ili9341_draw_box(8, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(8, 196, 0x1f, 1);
      return 3;
   }
   //loc_8001852
   if ((a > 60) && (a < 98) && (b > 195) && (b < 233))
   {
      //green
      ili9341_draw_box(61, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(61, 196, 0x7e0, 0);
      return 2;
   }
   //loc_8001894
   if ((a > 113) && (a < 151) && (b > 195) && (b < 233))
   {
      //red
      ili9341_draw_box(114, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(114, 196, 0xf800, 2);
      return 1;
   }
   //loc_80018d6
   if ((a > 166) && (a < 203) && (b > 195) && (b < 233))
   {
      //yellow
      ili9341_draw_box(167, 196, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(167, 196, 0xffe0, 3);
      return 4;
   }
   //loc_8001918
   if ((a > 78) && (a < 116) && (b > 5) && (b < 43))
   {
      //orange
      ili9341_draw_box(79, 6, 36, 36, 0xce59);
      sub_800c7e0(100);
      sub_8005198(79, 6, 0xfd20, 4);
      return 21;
   }
   //loc_800195a
   if ((a < 320) && (b > 47) && (b < 97))
   {
      return 6;
   }
   //loc_8001972
   if ((a > 274) && (a < 308) && (b > 197) && (b < 231))
   {
      //On-Off
      ili9341_draw_circle(291, 214, 16, 0xce59);
      sub_800c7e0(200);
      draw_on_off_icon(291, 214);
      return 14;
   }
   //loc_80019b2
   if ((a > 11) && (a < 63) && (b > 5) && (b < 43))
   {
      return 20;
   }
   //loc_80019ce
   if ((a > 141) && (a < 213) && (b > 6) && (b < 78))
   {
      return 22;
   }
   //loc_80019ea
   if ((a > 241) && (a < 307) && (b > 5) && (b < 43))
   {
      return 23;
   }

   return 0;
}


/* 8001bd8 - todo */
void sub_8001bd8(int a, int b, uint8_t c, uint8_t d)
{

}


/* 8001cc4 - todo */
void sub_8001cc4(int a, int b, void* c)
{

}


void sub_8001eb6()
{

}


/* 8001f04 - todo */
void sub_8001f04(void* a, int b)
{

}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  struct_8008d84* r7_c = (wData_20000a56 & 4)? Data_20000be8: Data_20000cc8;
  uint16_t r7_a = 10800;
  uint8_t r7_9;
  struct_8008d84_Inner8 r7; //???

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_I2C2_Init();
  MX_SPI2_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */

  ili9341_init();

  touch_init();

  HAL_TIM_Base_Start_IT(&htim5);

  sub_800b270();

  if (0 != sub_800a9a8())
  {
     sub_800173c(Data_20000a70,
                 &r7_c[bData_20000a58].Data_8,
				 bData_20000057,
				 &Data_20000a78,
				 Data_20000a78.bData_0x80,
				 bData_20000a58,
				 &Data_20000a5c,
  				 wData_20000a56
			 );
  }
  else
  {
     //loc_800c99c
     sub_80045f8(Data_20000a70, Data_20000a74, &Data_20000a4c, Data_20000a50.b1);
  }
  //loc_800c9b4
  __HAL_RTC_ALARM_ENABLE_IT(&hrtc, RTC_IT_SEC);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      //loc_800c9c4
	  if ((wData_20000a56 & 0x100) != 0)
	  {
         if ((wData_20000a56 & 0x10) != 0)
         {
            wData_20000a56 &= ~0x10;
            if (0 == HAL_RTC_GetTime(&hrtc, &Data_20000a70, RTC_FORMAT_BIN))
            {
               sub_8001ae8(Data_20000a70);
            }
            //loc_800ca06
            if ((Data_200023e0->wData_24 < 41) && (Data_200023e0->service_id != 0))
            {
               if (((wData_20000a56 & 0x80) == 0) &&
            		   (0 != sub_8008ed8(&Data_20000a70, &Data_20000a74)))
               {
                  if (0 != HAL_RTC_SetTime(&hrtc, &Data_20000a70, RTC_FORMAT_BIN))
                  {
                     Error_Handler();
                  }
                  //loc_800ca48
                  if (0 != HAL_RTC_SetDate(&hrtc, &Data_20000a74, RTC_FORMAT_BIN))
                  {
                     Error_Handler();
                  }
                  //loc_800ca5c
                  wData_20000a56 |= 0x80;

                  si46xx_mute(0);
               }
               //loc_800ca70
               if ((0 == sub_800a6ec(&Data_20000a5c)) &&
            		   (Data_20000a5c/5 != Data_20000a5a/5))
               {
           	      Data_20000a5a = Data_20000a5c;

                  sub_8001cc4(0x8e, 0x2a, &Data_20000a5c);
               }
               //->loc_800cb0c
            }
            else
            {
               //loc_800cabe
               if ((0 == sub_800a68c(&Data_20000a5c)) &&
             		   (Data_20000a5c/5 != Data_20000a5a/5))
               {
                  Data_20000a5a = Data_20000a5c;

                  sub_8001cc4(0x8e, 0x2a, &Data_20000a5c);
               }
               //loc_800cb0e
            }
            //loc_800cb0e
            if ((wData_20000a56 & 0x200) != 0)
            {
               if (bData_20000b7d == 0)
               {
                  wData_20000a56 &= ~0x200;
                  //->loc_800cbbe
               }
               else
               {
                  //loc_800cb78
                  if (Data_20000a70.Seconds == 0)
                  {
                     bData_20000b7d--;
                     if (bData_20000b7d == 0)
                     {
                        wData_20000a56 &= ~0x200;

                        sub_800aed0();

                        sub_80045f8(Data_20000a70, Data_20000a74, &Data_20000a4c, Data_20000a50.b1);
                     }
                  }
               }
            }
            //loc_800cbbe
            if ((wData_20000a56 & 0x400) == 0)
            {
               r7_a--;
               if (r7_a == 0)
               {
                  r7_a = 10800;

                  wData_20000a56 &= ~0x400;

                  sub_800aed0();

                  sub_80045f8(Data_20000a70, Data_20000a74, &Data_20000a4c, Data_20000a50.b1);
               }
            }
            //loc_800cc06
            if ((wData_20000a56 & 0x02) != 0)
            {
               sub_800abb0(&r7_c[bData_20000a58]);

               Data_20000a78.bData_0x80 = 0;

               sub_8001f04(&Data_20000a78, Data_20000a78.bData_0x80);
            }
            //loc_800cc42
         }
         //loc_800cc42
         if (0 == HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))
         {
            if ((Data_200023e0->wData_24 < 41) && (Data_200023e0->service_id != 0))
            {
               if (0 == sub_800a76c(&Data_20000a78, &Data_20000af8))
               {
                  sub_8001f04(&Data_20000a78, Data_20000a78.bData_0x80);
               }
               //loc_800cd5e
            }
            else
            {
               //loc_800cc84
               r7_9 = sub_80093a8(&r7,
            		   &Data_20000a78,
					   &Data_20000a70,
					   &Data_20000a74,
					   &Data_20000af8,
					   &wData_20000a56);

               if ((r7_9 & 4) != 0)
               {
                  if ((Data_20000a78.bData_0x80 != Data_20000afc.bData_0x80) ||
                		  (0 != memcmp(&Data_20000a78, &Data_20000afc, Data_20000a78.bData_0x80)))
                  {
                     //loc_800cccc
                     memcpy(&Data_20000afc, &Data_20000a78, 0x81); //??

                     sub_8001f04(&Data_20000a78, Data_20000a78.bData_0x80);
                  }
                  //loc_800cd5e
               }
               else
               {
                  //loc_800ccec
                  if ((r7_9 & 2) != 0)
                  {
                     if (0 != memcmp(&Data_200023e0->Data_8, &r7, 8))
                     {
//                        memcpy(Data_200023e0->fill8, r7, 8);
                        Data_200023e0->Data_8 = r7;

                        if ((wData_20000a56 & 0x04) != 0)
                        {
                           sub_8001a14(&Data_20000be8[bData_20000a58].Data_8);
                        }
                        else
                        {
                           //loc_800cd44
                           sub_8001a14(&Data_20000cc8[bData_20000a58].Data_8);
                        }
                     }
                  }
                  //loc_800cd5e
               }
            }
         } //if (0 == HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))
         //loc_800cd5e
         bData_20000a6d = 0;

         if (Data_20000a48.bData_0 == 0)
         {
            bData_20000a6d = Data_20000a48.bData_1;
            Data_20000a48.bData_0 = 1;
         }
         //loc_800cd7a
         bData_20000a6c = 0;

         if (Data_20000bc0.bData_0 == 0)
         {
            bData_20000a6c = sub_8001802(Data_20000bc0.wData_2, Data_20000bc0.wData_4);
         }
         //loc_800cda0
         if ((bData_20000a6c | bData_20000a6d))
         {
            //800cdb2
            r7_a = 10800;

            switch (bData_20000a6c | bData_20000a6d)
            {
            case 2:
               //800ce78 - green
               sub_800ac74();
               sub_8001bd8(0x0c, 0x06, bData_20000a58, wData_20000a56 & 0x04);
               sub_8001a14(&r7_c[bData_20000a58].Data_8);
               //->800D116
               break;

            case 3:
               //800ceb2 - blue
               sub_800acf0();
               sub_8001bd8(0x0c, 0x06, bData_20000a58, wData_20000a56 & 0x04);
               sub_8001a14(&r7_c[bData_20000a58].Data_8);
               //->800D116
               break;

            case 1:
               //800ceec - red
               sub_800adb8();
               sub_8001eb6(bData_20000057);
               //->800D116
               break;

            case 4:
               //800cefc - yellow
               sub_800ad68();
               sub_8001eb6(bData_20000057);
               break;

            case 14:
               //800cf0c - OnOff
               sub_800aed0();
               sub_80045f8(Data_20000a70, Data_20000a74, &Data_20000a4c, Data_20000a50.b1);
               //->800D116
               break;

            case 6:
               //800cf2a
               sub_800bd2c();

               Data_20000a78.bData_0x80 = 0;
#if 0
               sub_800173c(Data_20000a70,
            		   r7_C());
#endif
               //->800D116
               break;

            case 20:
               //800cf7a
               break;

            case 21:
               //800d010 - orange (Menu)
               menu_main();

               if (((wData_20000a56 & 0x04) != 0) && (bData_20000be4 == 0))
               {
                  bData_20000a58 = 0;
                  r7_c = Data_20000cc8;
                  wData_20000a56 &= ~0x04;
               }
               //800D040
               sub_800173c(Data_20000a70, &r7_c[bData_20000a58].Data_8, bData_20000057,
            		   &Data_20000a78, Data_20000a78.bData_0x80, bData_20000a58,
					   &Data_20000a5c, wData_20000a56);
               //->800D116
               break;

            case 22:
               //800d084
               break;

            case 23:
               //800d0cc
               break;

            default:
               //loc_800d114
               //goto loc_800c9c4;
               break;
            }

            Data_20000bc0.bData_0 = 1;
         }
         //goto loc_800c9c4;
	  }
	  else
	  {
         //loc_800d154
         if ((Data_20000bc0.bData_0 == 0) ||
        		 (Data_20000a48.bData_0 == 0))
         {
            //loc_800d164
            r7_a = 10800;

            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

            sub_800ae28();

            wData_20000a56 |= 0x02;

            sub_800173c(Data_20000a70,
                 &r7_c[bData_20000a58].Data_8,
   				 bData_20000057,
   				 &Data_20000a78,
				 Data_20000a78.bData_0x80,
				 bData_20000a58,
				 &Data_20000a5c,
  				 wData_20000a56
            	);

            Data_20000bc0.bData_0 = 1;
            //->loc_800d2ee
         }
         else
         {
            //loc_800d1d0
            if (((wData_20000a56 & 0x80) == 0) &&
            		(0 != sub_800af5c()))
            {
               sub_80045f8(Data_20000a70, Data_20000a74, &Data_20000a4c, Data_20000a50.b1);

               sub_800aed0();
            }
            //loc_800d202
            if ((wData_20000a56 & 0x10) != 0)
            {
               wData_20000a56 &= ~0x10;

               if (0 == HAL_RTC_GetTime(&hrtc, &Data_20000a70, RTC_FORMAT_BIN))
               {
                  sub_8001b60(Data_20000a70);
               }
               //loc_800d234
               if ((Data_20000a70.Seconds == 0) &&
            		   (Data_20000a70.Minutes == 0) &&
					   (Data_20000a70.Hours == 0) &&
					   (0 == HAL_RTC_GetDate(&hrtc, &Data_20000a74, RTC_FORMAT_BIN)))
               {
                  sub_80045f8(Data_20000a70, Data_20000a74, &Data_20000a4c, Data_20000a50.b1);
               }
               //loc_800d274
            }
            //loc_800d274
            if ((wData_20000a56 & 0x08) != 0)
            {
               wData_20000a56 &= ~0x08;

               HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

               sub_800ae28();

               wData_20000a56 |= 0x02;

               sub_800173c(Data_20000a70,
                           &r7_c[bData_20000a58].Data_8,
          				 bData_20000057,
          				 &Data_20000a78,
						 Data_20000a78.bData_0x80,
						 bData_20000a58,
						 &Data_20000a5c,
          				 wData_20000a56
          			 );
            }
            //loc_800c9c4
         }
         //loc_800d2ee
         //->loc_800c9c4
      }

	  //Tryouts....
#if 0
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  HAL_Delay(500);
#endif

#if 0
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
#endif


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV128;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_TUESDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x19;
  DateToUpdate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 720;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 4999;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 72;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1000;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Display_Backlight_Pin|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1 PC2 PC3 PC4 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Display_Backlight_Pin */
  GPIO_InitStruct.Pin = Display_Backlight_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Display_Backlight_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PD12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  /* USER CODE END FSMC_Init 0 */

  FSMC_NORSRAM_TimingTypeDef Timing = {0};

  /* USER CODE BEGIN FSMC_Init 1 */

  /* USER CODE END FSMC_Init 1 */

  /** Perform the SRAM1 memory initialization sequence
  */
  hsram1.Instance = FSMC_NORSRAM_DEVICE;
  hsram1.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram1.Init */
  hsram1.Init.NSBank = FSMC_NORSRAM_BANK1;
  hsram1.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram1.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  hsram1.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram1.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram1.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram1.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  hsram1.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram1.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  hsram1.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  hsram1.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  hsram1.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram1.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
  /* Timing */
  Timing.AddressSetupTime = 15;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 255;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&hsram1, &Timing, NULL) != HAL_OK)
  {
    Error_Handler( );
  }

  /** Disconnect NADV
  */

  __HAL_AFIO_FSMCNADV_DISCONNECTED();

  /* USER CODE BEGIN FSMC_Init 2 */

  /* USER CODE END FSMC_Init 2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
