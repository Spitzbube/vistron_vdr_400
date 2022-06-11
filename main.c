

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
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPEEN);

    // PE5 = Output for LED D2
    MODIFY_REG(GPIOE->CRL, GPIO_CRL_CNF5  + GPIO_CRL_MODE5,  GPIO_CRL_MODE5_0);

    // PE6 = Output for LED D3
    MODIFY_REG(GPIOE->CRL, GPIO_CRL_CNF6  + GPIO_CRL_MODE6,  GPIO_CRL_MODE6_0);

    while(1)
    {
        // LED Pin -> High
        WRITE_REG(GPIOE->BSRR, GPIO_BSRR_BR5);
        WRITE_REG(GPIOE->BSRR, GPIO_BSRR_BS6);
        delay(500);

        // LED Pin -> Low
        WRITE_REG(GPIOE->BSRR, GPIO_BSRR_BS5);
        WRITE_REG(GPIOE->BSRR, GPIO_BSRR_BR6);
        delay(500);
    }
}
