

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
    // Enable Port A and alternate functions
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN);

    // PA5 = Output for LED
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF5  + GPIO_CRL_MODE5,  GPIO_CRL_MODE5_0);

    while(1)
    {
        // LED Pin -> High
        WRITE_REG(GPIOA->BSRR, GPIO_BSRR_BS5);
        delay(500);

        // LED Pin -> Low
        WRITE_REG(GPIOA->BSRR, GPIO_BSRR_BR5);
        delay(500);
    }
}
