
#include "main.h"


/**
 * @brief  Initializes DWT_Clock_Cycle_Count for DWT_Delay_us function
 * @return Error DWT counter
 *         1: clock cycle counter not started
 *         0: clock cycle counter works
 */
uint32_t DWT_Delay_Init(void) {
  /* Disable TRC */
  CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
  /* Enable TRC */
  CoreDebug->DEMCR |=  CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

  /* Disable clock cycle counter */
  DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
  /* Enable  clock cycle counter */
  DWT->CTRL |=  DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

  /* Reset the clock cycle counter value */
  DWT->CYCCNT = 0;

     /* 3 NO OPERATION instructions */
     __ASM volatile ("NOP");
     __ASM volatile ("NOP");
  __ASM volatile ("NOP");

  /* Check if clock cycle counter has started */
     if(DWT->CYCCNT)
     {
       return 0; /*clock cycle counter started*/
     }
     else
  {
    return 1; /*clock cycle counter not started*/
  }
}


/**
 * @brief  This function provides a delay (in microseconds)
 * @param  microseconds: delay in microseconds
 */
__STATIC_INLINE void DWT_Delay_us(volatile uint32_t microseconds)
{
  uint32_t clk_cycle_start = DWT->CYCCNT;

  /* Go to number of cycles for system */
  microseconds *= (HAL_RCC_GetHCLKFreq() / 1000000);

  /* Delay till end */
  while ((DWT->CYCCNT - clk_cycle_start) < microseconds);
}



uint32_t data;
uint8_t count;
uint8_t addr;
uint8_t addr_inv;
uint8_t cmd;
uint8_t cmd_inv;

uint32_t receive_data (void)
{
	uint32_t code=0;

		  /* The START Sequence begin here
	   * there will be a pulse of 9ms LOW and
	   * than 4.5 ms space (HIGH)
	   */
	  while (!(HAL_GPIO_ReadPin (IR_RX_GPIO_Port, IR_RX_Pin)));  // wait for the pin to go high.. 9ms LOW

	  while ((HAL_GPIO_ReadPin (IR_RX_GPIO_Port, IR_RX_Pin)));  // wait for the pin to go low.. 4.5ms HIGH

	  /* START of FRAME ends here*/

	  /* DATA Reception
	   * We are only going to check the SPACE after 562.5us pulse
	   * if the space is 562.5us, the bit indicates '0'
	   * if the space is around 1.6ms, the bit is '1'
	   */

	  for (int i=0; i<32; i++)
	  {
		  count=0;

		  while (!(HAL_GPIO_ReadPin (IR_RX_GPIO_Port, IR_RX_Pin))); // wait for pin to go high.. this is 562.5us LOW

		  while ((HAL_GPIO_ReadPin (IR_RX_GPIO_Port, IR_RX_Pin)))  // count the space length while the pin is high
		  {
			  count++;
			  DWT_Delay_us(100);
		  }

		  if (count > 12) // if the space is more than 1.2 ms
		  {
			  code |= (1UL << (31-i));   // write 1
		  }

		  else code &= ~(1UL << (31-i));  // write 0
	  }

		return code;
}


void ir_init(void)
{
	DWT_Delay_Init();

	IrEvent.bData_0 = 1;
	IrEvent.bData_1 = 0;
}


void ir_poll(void)
{
	if (HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin) == 0)
	{
		data = receive_data();

		// sanity checks
		addr = (data >> 24) & 0xFF;
		addr_inv = (data >> 16) & 0xFF;
		cmd = (data >> 8) & 0xFF;
		cmd_inv = data & 0xFF;

		if ((addr == ((~addr_inv) & 0xFF)) && (cmd == ((~cmd_inv & 0xFF))))
		{
			if ((IrEvent.bData_0 != 0))
			{
				IrEvent.bData_0 = 0;
				IrEvent.bData_1 = cmd;
			}
		}
	}
}

