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
#include "cmsis_os.h"
#include "usb_device.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "../../User/func_8001ae8.h"
#include <stdlib.h>
#include "event_groups.h"

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

osThreadId defaultTaskHandle;
/* USER CODE BEGIN PV */

EventGroupHandle_t xEventGroup;
//TaskHandle_t foregroundTaskHandle;
#if 0
osThreadId_t foregroundTaskHandle;
const osThreadAttr_t foregroundTask_attributes = {
  .name = "foregroundTask",
  .stack_size = 200,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
#else
osThreadId foregroundTaskHandle;
#endif

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM6_Init(void);
static void MX_FSMC_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */

void main_foreground_task(void*);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* 800c7e0 - todo */
void main_delay(uint16_t a)
{
#if 0
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
#else
//   TickType_t ticks = xTaskGetTickCount();
//   osDelay(a);
   HAL_Delay(a);
//   vTaskDelay(pdMS_TO_TICKS(a));
//   printf("main_delay: a=%u, ticks=%u\n\r", a, xTaskGetTickCount() - ticks);
#endif
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


int _write(int file, char *ptr, int len)
{
#if 0
   uint8_t rc = USBD_OK;

   do
   {
      rc = CDC_Transmit_FS((uint8_t*) ptr, len);
   }
   while (USBD_BUSY == rc);
#else
   HAL_UART_Transmit(&huart2, ptr, len, HAL_MAX_DELAY);
#endif

   return len;
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  //800c8f4
#if 0
  Tuner_Channel* pChannels/*r7_c*/ = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)?
		  FavouriteList: ChannelList;
  uint16_t standbyCounter = 10800;
  uint8_t r7_9;
  struct_8008d84_Inner8 r7; //???
#endif

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
  MX_FSMC_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

#if 0
  
  ili9341_init();

  touch_init();
  
  HAL_TIM_Base_Start_IT(&htim5);
  
  channel_list_clear();

  //Pull up USB D+ to indicate the USB host our presence on the bus
  HAL_GPIO_WritePin(USB_DP_Pull_GPIO_Port, USB_DP_Pull_Pin, GPIO_PIN_SET);

  if (0 != sub_800a9a8())
  {
     draw_main_screen(rtcTime,
                 &pChannels[bCurrentChannelNumber].Data_8,
				 bCurrentVolume,
				 &radioText,
				 radioText.bLength,
				 bCurrentChannelNumber,
				 &Data_20000a5c,
  				 wMainloopEvents
			 );
  }
  else //if (0 != sub_800a9a8())
  {
     //loc_800c99c
     draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
  }
  //loc_800c9b4

  __HAL_RTC_ALARM_ENABLE_IT(&hrtc, RTC_IT_SEC);

#endif
  
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  xEventGroup = xEventGroupCreate();
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 200);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
#if 0
  xTaskCreate(main_foreground_task, "ForegroundTask", 2*configMINIMAL_STACK_SIZE, NULL, 0/*20*/, &foregroundTaskHandle);
#else
#if 1
  osThreadDef(foregroundTask, main_foreground_task, osPriorityNormal, 0, 200);
  foregroundTaskHandle = osThreadCreate(osThread(foregroundTask), NULL);
#else
  foregroundTaskHandle = osThreadNew(main_foreground_task, NULL, &foregroundTask_attributes);
#endif
#endif
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#if 0

#if 0
	  uint8_t Buf[] = "Mainloop\r\n";

	  CDC_Transmit_FS(Buf, sizeof(Buf)+1);
#else
//	  printf("Mainloop\r\n");
#endif

      //loc_800c9c4
	  if ((wMainloopEvents & MAIN_LOOP_EVENT_FOREGROUND) != 0)
	  {
         if ((wMainloopEvents & MAIN_LOOP_EVENT_RTC) != 0)
         {
            wMainloopEvents &= ~MAIN_LOOP_EVENT_RTC;
            if (0 == HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
            {
               draw_foreground_clock(rtcTime);
            }
            //loc_800ca06
            if ((Data_200023e0->frequency < 41) && (Data_200023e0->service_id != 0))
            {
               if (((wMainloopEvents & MAIN_LOOP_EVENT_BACKGROUND_TIME) == 0) &&
            		   (0 != si46xx_dab_get_time_date(&rtcTime, &rtcDate)))
               {
                  if (0 != HAL_RTC_SetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
                  {
                     Error_Handler();
                  }
                  //loc_800ca48
                  if (0 != HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN))
                  {
                     Error_Handler();
                  }
                  //loc_800ca5c
                  wMainloopEvents |= MAIN_LOOP_EVENT_BACKGROUND_TIME;

                  si46xx_mute(0);
               }
               //loc_800ca70
               if ((0 == si46xx_get_dab_values(&Data_20000a5c)) &&
            		   (Data_20000a5c.rssi/5 != Data_20000a5a/5))
               {
           	      Data_20000a5a = Data_20000a5c.rssi;

                  draw_signal_strength_bars(142, 42, &Data_20000a5c.rssi);
               }
               //->loc_800cb0c
            }
            else
            {
               //loc_800cabe
               if ((0 == si46xx_get_fm_values(&Data_20000a5c)) &&
             		   (Data_20000a5c.rssi/5 != Data_20000a5a/5))
               {
                  Data_20000a5a = Data_20000a5c.rssi;

                  draw_signal_strength_bars(142, 42, &Data_20000a5c.rssi);
               }
               //loc_800cb0e
            }

            //loc_800cb0e: Sleep Timer

            if ((wMainloopEvents & MAIN_LOOP_EVENT_SLEEP_TIMER) != 0)
            {
               if (sleepTimerCount == 0)
               {
                  wMainloopEvents &= ~MAIN_LOOP_EVENT_SLEEP_TIMER;
                  //->loc_800cbbe
               }
               else
               {
                  //loc_800cb78
                  if (rtcTime.Seconds == 0)
                  {
                     sleepTimerCount--;
                     if (sleepTimerCount == 0)
                     {
                        wMainloopEvents &= ~MAIN_LOOP_EVENT_SLEEP_TIMER;

                        channel_stop_playing();

                        draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
                     }
                  }
               }
            }

            //loc_800cbbe: Auto-Standby

            if ((wMainloopEvents & MAIN_LOOP_EVENT_AUTO_STANDBY) == 0)
            {
               standbyCounter--;
               if (standbyCounter == 0)
               {
                  standbyCounter = 10800;

                  wMainloopEvents &= ~MAIN_LOOP_EVENT_AUTO_STANDBY;

                  channel_stop_playing();

                  draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
               }
            }
            //loc_800cc06
            if ((wMainloopEvents & 0x02) != 0)
            {
               channel_set(&pChannels[bCurrentChannelNumber]);

               radioText.bLength = 0;

               draw_radio_text(&radioText, radioText.bLength);
            }
            //loc_800cc42
         } //if ((wMainloopEvents & MAIN_LOOP_EVENT_RTC) != 0)

         //loc_800cc42: Poll the SI46xx Interrup Pin

         if (0 == HAL_GPIO_ReadPin(SI46xx_Interrupt_GPIO_Port, SI46xx_Interrupt_Pin))
         {
        	 HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

            if ((Data_200023e0->frequency < 41) && (Data_200023e0->service_id != 0))
            {
               if (0 == si46xx_get_digital_service_data(radioText.str, &radioText.bLength))
               {
                  draw_radio_text(&radioText, radioText.bLength);

                  printf("DAB Text: '%.*s'\r\n", radioText.bLength, radioText.str);
               }
               //loc_800cd5e
            }
            else
            {
               //loc_800cc84
               r7_9 = si46xx_fm_get_rds_data(&r7,
            		   radioText.str,
					   &rtcTime,
					   &rtcDate,
					   &wMainloopEvents,
					   &radioText.bLength);

               if ((r7_9 & 4) != 0)
               {
                  if ((radioText.bLength != radioTextOld.bLength) ||
                		  (0 != memcmp(radioText.str, &radioTextOld, radioText.bLength)))
                  {
                     //loc_800cccc
                     memcpy(&radioTextOld, &radioText, sizeof(Radio_Text));

                     draw_radio_text(&radioText, radioText.bLength);

                     printf("FM Text: '%.*s'\r\n", radioText.bLength, radioText.str);
                  }
                  //loc_800cd5e
               }
               //loc_800ccec
               else if ((r7_9 & 2) != 0)
               {
                  if (0 != memcmp(&Data_200023e0->Data_8, &r7, 8))
                  {
//                     memcpy(Data_200023e0->fill8, r7, 8);
                     Data_200023e0->Data_8 = r7;

                     if ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0)
                     {
                        draw_channel_name(&FavouriteList[bCurrentChannelNumber].Data_8);
                     }
                     else
                     {
                        //loc_800cd44
                        draw_channel_name(&ChannelList[bCurrentChannelNumber].Data_8);
                     }
                  }
                  //loc_800cd5e
               }
            }

            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

         } //if (0 == HAL_GPIO_ReadPin(SI46xx_Interrupt_GPIO_Port, SI46xx_Interrupt_Pin))
         //loc_800cd5e
         bMainKeyCode = 0;
         if (KeyEvent.bData_0 == 0)
         {
            bMainKeyCode = KeyEvent.bData_1;
            KeyEvent.bData_0 = 1;
         }
         //loc_800cd7a
         bMainTouchCode = 0;
         if (TouchEvent.bData_0 == 0)
         {
            bMainTouchCode = main_screen_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
         }
         //loc_800cda0
         if ((bMainTouchCode | bMainKeyCode))
         {
            //800cdb2
            standbyCounter = 10800;

            switch (bMainTouchCode | bMainKeyCode)
            {
            case 2:
               //800ce78 - green
               channel_next();
               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
               //->800D116
               break;

            case 3:
               //800ceb2 - blue
               channel_previous();
               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
               //->800D116
               break;

            case 1:
               //800ceec - red
               volume_down();
               draw_volume_bar(bCurrentVolume);
               //->800D116
               break;

            case 4:
               //800cefc - yellow
               volume_up();
               draw_volume_bar(bCurrentVolume);
               break;

            case 14:
               //800cf0c - OnOff
               channel_stop_playing();
               draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
               //->800D116
               break;

            case 6:
               //800cf2a
               menu_channel_select();

               radioText.bLength = 0;

               draw_main_screen(rtcTime,
            		   &pChannels[bCurrentChannelNumber].Data_8,
					   bCurrentVolume,
            		   &radioText,
					   radioText.bLength,
					   bCurrentChannelNumber,
					   &Data_20000a5c,
					   wMainloopEvents);
               //->800D116
               break;

            case 20:
               //800cf7a - Channel number box
               if ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0)
               {
                  bCurrentChannelNumber = 0;
                  wMainloopEvents &= ~MAIN_LOOP_EVENT_FAV_ACTIVE;
                  wMainloopEvents |= 0x02;
                  //->800CFC6
               }
               else
               {
                  //800CFAA
                  if (bFavouriteCount != 0)
                  {
                     bCurrentChannelNumber = 0;
                     wMainloopEvents |= (0x02|MAIN_LOOP_EVENT_FAV_ACTIVE);
                  }
                  //800CFC6
               }
               //800CFC6
               pChannels = ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0)? FavouriteList: ChannelList;

               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
               //800CFD6
               break;

            case 21:
               //800d010 - orange (Menu)
               menu_main();

               if (((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0) && (bFavouriteCount == 0))
               {
                  bCurrentChannelNumber = 0;
                  pChannels = ChannelList;
                  wMainloopEvents &= ~MAIN_LOOP_EVENT_FAV_ACTIVE;
               }
               //800D040
               draw_main_screen(rtcTime,
            		   &pChannels[bCurrentChannelNumber].Data_8,
					   bCurrentVolume,
            		   &radioText,
					   radioText.bLength,
					   bCurrentChannelNumber,
					   &Data_20000a5c,
					   wMainloopEvents);
               //->800D116
               break;

            case 22:
               //800d084
               menu_signal_information();

               draw_main_screen(rtcTime,
            		   &pChannels[bCurrentChannelNumber].Data_8,
					   bCurrentVolume,
            		   &radioText,
					   radioText.bLength,
					   bCurrentChannelNumber,
					   &Data_20000a5c,
					   wMainloopEvents);
               //->800D116
               break;

            case 23:
               //800d0cc
               menu_volume_change();

               draw_main_screen(rtcTime,
            		   &pChannels[bCurrentChannelNumber].Data_8,
					   bCurrentVolume,
            		   &radioText,
					   radioText.bLength,
					   bCurrentChannelNumber,
					   &Data_20000a5c,
					   wMainloopEvents);
               break;

            default:
               //loc_800d114
               //goto loc_800c9c4;
               break;
            }

            TouchEvent.bData_0 = 1;
         }
         //goto loc_800c9c4;
	  } //if ((wMainloopEvents & MAIN_LOOP_EVENT_FOREGROUND) != 0)
	  else
	  {
         //loc_800d154
         if ((TouchEvent.bData_0 == 0) ||
        		 (KeyEvent.bData_0 == 0))
         {
            //loc_800d164
            standbyCounter = 10800;

            // Display On
            HAL_GPIO_WritePin(Display_Backlight_GPIO_Port, Display_Backlight_Pin, GPIO_PIN_RESET);

            channel_start_current();

            wMainloopEvents |= 0x02;

            draw_main_screen(rtcTime,
                 &pChannels[bCurrentChannelNumber].Data_8,
   				 bCurrentVolume,
   				 &radioText,
				 radioText.bLength,
				 bCurrentChannelNumber,
				 &Data_20000a5c,
  				 wMainloopEvents
            	);

            TouchEvent.bData_0 = 1;
            //->loc_800d2ee
         }
         else
         {
            //loc_800d1d0
            if (((wMainloopEvents & MAIN_LOOP_EVENT_BACKGROUND_TIME) == 0) &&
            		(0 != channel_search_time()))
            {
               draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);

               channel_stop_playing();
            }
            //loc_800d202
            if ((wMainloopEvents & MAIN_LOOP_EVENT_RTC) != 0)
            {
               wMainloopEvents &= ~MAIN_LOOP_EVENT_RTC;

               if (0 == HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
               {
                  draw_background_clock(rtcTime);
               }
               //loc_800d234
               if ((rtcTime.Seconds == 0) &&
            		   (rtcTime.Minutes == 0) &&
					   (rtcTime.Hours == 0) &&
					   (0 == HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN)))
               {
                  draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
               }
               //loc_800d274
            }

            //loc_800d274: Alarm

            if ((wMainloopEvents & MAIN_LOOP_EVENT_ALARM) != 0)
            {
               wMainloopEvents &= ~MAIN_LOOP_EVENT_ALARM;

               HAL_GPIO_WritePin(Display_Backlight_GPIO_Port, Display_Backlight_Pin, GPIO_PIN_RESET);

               channel_start_current();

               wMainloopEvents |= 0x02;

               draw_main_screen(rtcTime,
                           &pChannels[bCurrentChannelNumber].Data_8,
          				 bCurrentVolume,
          				 &radioText,
						 radioText.bLength,
						 bCurrentChannelNumber,
						 &Data_20000a5c,
          				 wMainloopEvents
          			 );
            }
            //loc_800c9c4
         }
         //loc_800d2ee
         //->loc_800c9c4
      }

	  //Tryouts....
#if 0
	  HAL_GPIO_WritePin(Display_Backlight_GPIO_Port, Display_Backlight_Pin, GPIO_PIN_RESET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(Display_Backlight_GPIO_Port, Display_Backlight_Pin, GPIO_PIN_SET);
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

#endif

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  } //while (1)

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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV128;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
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

  //800d3e4

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

  //800d440

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
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

  //800d4d4

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

  //800d540

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

  //800d5dc

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED1_Pin|LED2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|SI46xx_Reset_Pin|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Display_Backlight_Pin|Touch_SPI_MOSI_Pin|USB_DP_Pull_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI2_CS_SI46xx_GPIO_Port, SPI2_CS_SI46xx_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Touch_SPI_CLK_GPIO_Port, Touch_SPI_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Touch_SPI_CS_GPIO_Port, Touch_SPI_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED1_Pin LED2_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : SI46xx_Interrupt_Pin */
  GPIO_InitStruct.Pin = SI46xx_Interrupt_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SI46xx_Interrupt_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1 SI46xx_Reset_Pin PC3 PC4 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|SI46xx_Reset_Pin|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 USB_DP_Pull_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_1|USB_DP_Pull_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : Button_Blue_Pin */
  GPIO_InitStruct.Pin = Button_Blue_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button_Blue_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Display_Backlight_Pin */
  GPIO_InitStruct.Pin = Display_Backlight_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Display_Backlight_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Touch_SPI_MISO_Pin */
  GPIO_InitStruct.Pin = Touch_SPI_MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Touch_SPI_MISO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Touch_SPI_MOSI_Pin */
  GPIO_InitStruct.Pin = Touch_SPI_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(Touch_SPI_MOSI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Button_Yellow_Pin */
  GPIO_InitStruct.Pin = Button_Yellow_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button_Yellow_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Button_Red_Pin Button_Green_Pin */
  GPIO_InitStruct.Pin = Button_Red_Pin|Button_Green_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI2_CS_SI46xx_Pin Touch_SPI_CS_Pin */
  GPIO_InitStruct.Pin = SPI2_CS_SI46xx_Pin|Touch_SPI_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Touch_SPI_CLK_Pin */
  GPIO_InitStruct.Pin = Touch_SPI_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(Touch_SPI_CLK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Touch_Interrupt_Pin */
  GPIO_InitStruct.Pin = Touch_Interrupt_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Touch_Interrupt_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* FSMC initialization function */
static void MX_FSMC_Init(void)
{

  /* USER CODE BEGIN FSMC_Init 0 */

  //800d8cc

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

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 5 */

  Tuner_Channel* pChannels = (wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE)?
				  FavouriteList: ChannelList;

  ili9341_init();

  touch_init();

  HAL_TIM_Base_Start_IT(&htim5);

  channel_list_clear();

#if 0
  //Pull up USB D+ to indicate the USB host our presence on the bus
  HAL_GPIO_WritePin(USB_DP_Pull_GPIO_Port, USB_DP_Pull_Pin, GPIO_PIN_SET);
#endif

  if (0 != sub_800a9a8())
  {
#if 0
     draw_main_screen(rtcTime,
                 &pChannels[bCurrentChannelNumber].Data_8,
				 bCurrentVolume,
				 &radioText,
				 radioText.bLength,
				 bCurrentChannelNumber,
				 &Data_20000a5c,
  				 wMainloopEvents
			 );
#else
     xEventGroupSetBits(xEventGroup, EVENTGROUP_BIT_BACKGROUND);
#endif
  }
  else //if (0 != sub_800a9a8())
  {
     //loc_800c99c
//     draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
//     vTaskResume(backgroundTaskHandle);
//     vTaskSuspend(NULL);

	  xEventGroupSetBits(xEventGroup, EVENTGROUP_BIT_BACKGROUND);
  }
  //loc_800c9b4
  __HAL_RTC_ALARM_ENABLE_IT(&hrtc, RTC_IT_SEC);

  EventBits_t uxBits;
  EventBits_t uxExpectBits = EVENTGROUP_BIT_BACKGROUND;

  /* Infinite loop */
  for(;;)
  {
    //HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

	uxBits = xEventGroupWaitBits(xEventGroup, uxExpectBits, pdFALSE, pdFALSE, portMAX_DELAY);

    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);

//    HAL_UART_Transmit(&huart2, uartBuffer, strlen(uartBuffer), HAL_MAX_DELAY);

	if ((uxBits & EVENTGROUP_BIT_BACKGROUND) != 0)
	{
	     xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_BACKGROUND);

         draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);

	     uxExpectBits |= EVENTGROUP_BIT_TOUCH|EVENTGROUP_BIT_RTC;
	}

#if 0
      //loc_800c9c4
	  if ((wMainloopEvents & MAIN_LOOP_EVENT_FOREGROUND) != 0)
	  {
         if ((wMainloopEvents & MAIN_LOOP_EVENT_RTC) != 0)
         {
            wMainloopEvents &= ~MAIN_LOOP_EVENT_RTC;
            if (0 == HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
            {
               draw_foreground_clock(rtcTime);
            }
            //loc_800ca06
            if ((Data_200023e0->frequency < 41) && (Data_200023e0->service_id != 0))
            {
               if (((wMainloopEvents & MAIN_LOOP_EVENT_BACKGROUND_TIME) == 0) &&
            		   (0 != si46xx_dab_get_time_date(&rtcTime, &rtcDate)))
               {
                  if (0 != HAL_RTC_SetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
                  {
                     Error_Handler();
                  }
                  //loc_800ca48
                  if (0 != HAL_RTC_SetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN))
                  {
                     Error_Handler();
                  }
                  //loc_800ca5c
                  wMainloopEvents |= MAIN_LOOP_EVENT_BACKGROUND_TIME;

                  si46xx_mute(0);
               }
               //loc_800ca70
               if ((0 == si46xx_get_dab_values(&Data_20000a5c)) &&
            		   (Data_20000a5c.rssi/5 != Data_20000a5a/5))
               {
           	      Data_20000a5a = Data_20000a5c.rssi;

                  draw_signal_strength_bars(142, 42, &Data_20000a5c.rssi);
               }
               //->loc_800cb0c
            }
            else
            {
               //loc_800cabe
               if ((0 == si46xx_get_fm_values(&Data_20000a5c)) &&
             		   (Data_20000a5c.rssi/5 != Data_20000a5a/5))
               {
                  Data_20000a5a = Data_20000a5c.rssi;

                  draw_signal_strength_bars(142, 42, &Data_20000a5c.rssi);
               }
               //loc_800cb0e
            }

            //loc_800cb0e: Sleep Timer

            if ((wMainloopEvents & MAIN_LOOP_EVENT_SLEEP_TIMER) != 0)
            {
               if (sleepTimerCount == 0)
               {
                  wMainloopEvents &= ~MAIN_LOOP_EVENT_SLEEP_TIMER;
                  //->loc_800cbbe
               }
               else
               {
                  //loc_800cb78
                  if (rtcTime.Seconds == 0)
                  {
                     sleepTimerCount--;
                     if (sleepTimerCount == 0)
                     {
                        wMainloopEvents &= ~MAIN_LOOP_EVENT_SLEEP_TIMER;

                        channel_stop_playing();

                        draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
                     }
                  }
               }
            }

            //loc_800cbbe: Auto-Standby

            if ((wMainloopEvents & MAIN_LOOP_EVENT_AUTO_STANDBY) == 0)
            {
               standbyCounter--;
               if (standbyCounter == 0)
               {
                  standbyCounter = 10800;

                  wMainloopEvents &= ~MAIN_LOOP_EVENT_AUTO_STANDBY;

                  channel_stop_playing();

                  draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
               }
            }
            //loc_800cc06
            if ((wMainloopEvents & 0x02) != 0)
            {
               channel_set(&pChannels[bCurrentChannelNumber]);

               radioText.bLength = 0;

               draw_radio_text(&radioText, radioText.bLength);
            }
            //loc_800cc42
         } //if ((wMainloopEvents & MAIN_LOOP_EVENT_RTC) != 0)

#if 0
         //loc_800cc42: Poll the SI46xx Interrup Pin

         if (0 == HAL_GPIO_ReadPin(SI46xx_Interrupt_GPIO_Port, SI46xx_Interrupt_Pin))
         {
        	 HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

            if ((Data_200023e0->frequency < 41) && (Data_200023e0->service_id != 0))
            {
               if (0 == si46xx_get_digital_service_data(radioText.str, &radioText.bLength))
               {
                  draw_radio_text(&radioText, radioText.bLength);

//                  printf("DAB Text: '%.*s'\r\n", radioText.bLength, radioText.str);
               }
               //loc_800cd5e
            }
            else
            {
               //loc_800cc84
               struct_8008d84_Inner8 r7;
               uint8_t r7_9;

               r7_9 = si46xx_fm_get_rds_data(&r7,
            		   radioText.str,
					   &rtcTime,
					   &rtcDate,
					   &wMainloopEvents,
					   &radioText.bLength);

               if ((r7_9 & 4) != 0)
               {
                  if ((radioText.bLength != radioTextOld.bLength) ||
                		  (0 != memcmp(radioText.str, &radioTextOld, radioText.bLength)))
                  {
                     //loc_800cccc
                     memcpy(&radioTextOld, &radioText, sizeof(Radio_Text));

                     draw_radio_text(&radioText, radioText.bLength);

//                     printf("FM Text: '%.*s'\r\n", radioText.bLength, radioText.str);
                  }
                  //loc_800cd5e
               }
               //loc_800ccec
               else if ((r7_9 & 2) != 0)
               {
                  if (0 != memcmp(&Data_200023e0->Data_8, &r7, 8))
                  {
//                     memcpy(Data_200023e0->fill8, r7, 8);
                     Data_200023e0->Data_8 = r7;

                     if ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0)
                     {
                        draw_channel_name(&FavouriteList[bCurrentChannelNumber].Data_8);
                     }
                     else
                     {
                        //loc_800cd44
                        draw_channel_name(&ChannelList[bCurrentChannelNumber].Data_8);
                     }
                  }
                  //loc_800cd5e
               }
            }

            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

         } //if (0 == HAL_GPIO_ReadPin(SI46xx_Interrupt_GPIO_Port, SI46xx_Interrupt_Pin))
#endif

         //loc_800cd5e
         bMainKeyCode = 0;
         if (KeyEvent.bData_0 == 0)
         {
            bMainKeyCode = KeyEvent.bData_1;
            KeyEvent.bData_0 = 1;
         }
         //loc_800cd7a
         bMainTouchCode = 0;
         if (TouchEvent.bData_0 == 0)
         {
            bMainTouchCode = main_screen_check_touch_fields(TouchEvent.wData_2, TouchEvent.wData_4);
         }
         //loc_800cda0
         if ((bMainTouchCode | bMainKeyCode))
         {
            //800cdb2
            standbyCounter = 10800;

            switch (bMainTouchCode | bMainKeyCode)
            {
            case 2:
               //800ce78 - green
               channel_next();
               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
               //->800D116
               break;

            case 3:
               //800ceb2 - blue
               channel_previous();
               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
               //->800D116
               break;

            case 1:
               //800ceec - red
               volume_down();
               draw_volume_bar(bCurrentVolume);
               //->800D116
               break;

            case 4:
               //800cefc - yellow
               volume_up();
               draw_volume_bar(bCurrentVolume);
               break;

            case 14:
               //800cf0c - OnOff
               channel_stop_playing();
               draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
               //->800D116
               break;

            case 6:
               //800cf2a
               menu_channel_select();

               radioText.bLength = 0;

               draw_main_screen(rtcTime,
            		   &pChannels[bCurrentChannelNumber].Data_8,
					   bCurrentVolume,
            		   &radioText,
					   radioText.bLength,
					   bCurrentChannelNumber,
					   &Data_20000a5c,
					   wMainloopEvents);
               //->800D116
               break;

            case 20:
               //800cf7a - Channel number box
               if ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0)
               {
                  bCurrentChannelNumber = 0;
                  wMainloopEvents &= ~MAIN_LOOP_EVENT_FAV_ACTIVE;
                  wMainloopEvents |= 0x02;
                  //->800CFC6
               }
               else
               {
                  //800CFAA
                  if (bFavouriteCount != 0)
                  {
                     bCurrentChannelNumber = 0;
                     wMainloopEvents |= (0x02|MAIN_LOOP_EVENT_FAV_ACTIVE);
                  }
                  //800CFC6
               }
               //800CFC6
               pChannels = ((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0)? FavouriteList: ChannelList;

               draw_channel_name(&pChannels[bCurrentChannelNumber].Data_8);
               draw_channel_number_box(12, 6, bCurrentChannelNumber, wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE);
               //800CFD6
               break;

            case 21:
               //800d010 - orange (Menu)
               menu_main();

               if (((wMainloopEvents & MAIN_LOOP_EVENT_FAV_ACTIVE) != 0) && (bFavouriteCount == 0))
               {
                  bCurrentChannelNumber = 0;
                  pChannels = ChannelList;
                  wMainloopEvents &= ~MAIN_LOOP_EVENT_FAV_ACTIVE;
               }
               //800D040
               draw_main_screen(rtcTime,
            		   &pChannels[bCurrentChannelNumber].Data_8,
					   bCurrentVolume,
            		   &radioText,
					   radioText.bLength,
					   bCurrentChannelNumber,
					   &Data_20000a5c,
					   wMainloopEvents);
               //->800D116
               break;

            case 22:
               //800d084
               menu_signal_information();

               draw_main_screen(rtcTime,
            		   &pChannels[bCurrentChannelNumber].Data_8,
					   bCurrentVolume,
            		   &radioText,
					   radioText.bLength,
					   bCurrentChannelNumber,
					   &Data_20000a5c,
					   wMainloopEvents);
               //->800D116
               break;

            case 23:
               //800d0cc
               menu_volume_change();

               draw_main_screen(rtcTime,
            		   &pChannels[bCurrentChannelNumber].Data_8,
					   bCurrentVolume,
            		   &radioText,
					   radioText.bLength,
					   bCurrentChannelNumber,
					   &Data_20000a5c,
					   wMainloopEvents);
               break;

            default:
               //loc_800d114
               //goto loc_800c9c4;
               break;
            }

            TouchEvent.bData_0 = 1;
         } //if ((bMainTouchCode | bMainKeyCode))
         //goto loc_800c9c4;
	  } //if ((wMainloopEvents & MAIN_LOOP_EVENT_FOREGROUND) != 0)
	  else
#endif

	  if ((uxBits & EVENTGROUP_BIT_TOUCH) != 0)
	  {
         //loc_800d154
         if ((TouchEvent.bData_0 == 0) ||
        		 (KeyEvent.bData_0 == 0))
         {
            TouchEvent.bData_0 = 1;

			xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_TOUCH);

			uxExpectBits = EVENTGROUP_BIT_BACKGROUND; //wait for background

			xEventGroupSetBits(xEventGroup, EVENTGROUP_BIT_FOREGROUND);

//			vTaskSuspend(NULL); //wait for background
         }
         else
         {
            //loc_800d1d0^
#if 0
            if (((wMainloopEvents & MAIN_LOOP_EVENT_BACKGROUND_TIME) == 0) &&
            		(0 != channel_search_time()))
            {
               draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);

               channel_stop_playing();
            }
#endif
            //loc_800d202
#if 0
            if ((wMainloopEvents & MAIN_LOOP_EVENT_RTC) != 0)
            {
               wMainloopEvents &= ~MAIN_LOOP_EVENT_RTC;

               if (0 == HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
               {
                  draw_background_clock(rtcTime);
               }
               //loc_800d234
               if ((rtcTime.Seconds == 0) &&
            		   (rtcTime.Minutes == 0) &&
					   (rtcTime.Hours == 0) &&
					   (0 == HAL_RTC_GetDate(&hrtc, &rtcDate, RTC_FORMAT_BIN)))
               {
                  draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);
               }
               //loc_800d274
            }
#endif
            //loc_800d274: Alarm

            if ((wMainloopEvents & MAIN_LOOP_EVENT_ALARM) != 0)
            {
               wMainloopEvents &= ~MAIN_LOOP_EVENT_ALARM;

               HAL_GPIO_WritePin(Display_Backlight_GPIO_Port, Display_Backlight_Pin, GPIO_PIN_RESET);

               channel_start_current();

               wMainloopEvents |= 0x02;

               draw_main_screen(rtcTime,
                           &pChannels[bCurrentChannelNumber].Data_8,
          				 bCurrentVolume,
          				 &radioText,
						 radioText.bLength,
						 bCurrentChannelNumber,
						 &Data_20000a5c,
          				 wMainloopEvents
          			 );
            }
            //loc_800c9c4
         }
         //loc_800d2ee
         //->loc_800c9c4
      } //if ((uxBits & EVENTGROUP_BIT_TOUCH) != 0)

	  if ((uxBits & EVENTGROUP_BIT_RTC) != 0)
	  {
		  xEventGroupClearBits(xEventGroup, EVENTGROUP_BIT_RTC);

          if (0 == HAL_RTC_GetTime(&hrtc, &rtcTime, RTC_FORMAT_BIN))
          {
             draw_background_clock(rtcTime);
          }
	  }

      if (((wMainloopEvents & MAIN_LOOP_EVENT_BACKGROUND_TIME) == 0) &&
      		(0 != channel_search_time()))
      {
         draw_standby_screen(rtcTime, rtcDate, &currentAlarmTime, UserSettings.b1);

         channel_stop_playing();
      }

  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */

  //800d994

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
