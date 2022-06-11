
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f1xx.h"

// delay loop for 8 MHz CPU clock with optimizer enabled
void delay(uint32_t msec)
{
    for (uint32_t j=0; j < 500UL * msec; j++)
    {
        __NOP();
    }
}

int main(void)
{
    // Enable Port E and alternate functions
    RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;

    // PE5 = Output for LED D2
    // PE6 = Output for LED D3
    GPIOE->CRL &= ~(GPIO_CRL_CNF6 + GPIO_CRL_MODE6 + GPIO_CRL_CNF5 + GPIO_CRL_MODE5);
    GPIOE->CRL |= GPIO_CRL_MODE6_0 + GPIO_CRL_MODE5_0;

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

	vTaskStartScheduler();  // should never return
}

void vApplicationTickHook(void)
{
	static int on=1;

	if (on)
	{
		GPIOE->BSRR |= GPIO_BSRR_BR5;
		on = 0;
	}
	else
	{
	    GPIOE->BSRR |= GPIO_BSRR_BS5;
	    on = 1;
	}
}

void vApplicationIdleHook(void)
{
	static int on=1;

	if (on)
	{
		GPIOE->BSRR |= GPIO_BSRR_BR6;
		on = 0;
	}
	else
	{
	    GPIOE->BSRR |= GPIO_BSRR_BS6;
	    on = 1;
	}
    delay(500);
}

