

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

    while(1)
    {
        // LED Pin -> High
        GPIOE->BSRR |= GPIO_BSRR_BR5;
        GPIOE->BSRR |= GPIO_BSRR_BS6;
        delay(500);

        // LED Pin -> Low
        GPIOE->BSRR |= GPIO_BSRR_BS5;
        GPIOE->BSRR |= GPIO_BSRR_BR6;
        delay(500);
    }
}
