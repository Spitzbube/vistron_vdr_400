/*
* STM32 HID Bootloader - USB HID bootloader for STM32F10X
* Copyright (c) 2018 Bruno Freitas - bruno@brunofreitas.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stm32f10x.h>
//#include "stm32f1xx.h"

#include "usb.h"
#include "hid.h"
#include "bitwise.h"


void delay(uint32_t msec)
{
    for (uint32_t j=0; j < 500UL * msec; j++)
    {
        __NOP();
    }
}


// HID Bootloader takes 4K
#define USER_PROGRAM 0x08001000

int main() {
	uint32_t usrSp = *(volatile uint32_t *)USER_PROGRAM;
	uint32_t usrMain = *(volatile uint32_t *)(USER_PROGRAM + 0x04); /* reset ptr in vector table */

	SystemCoreClockUpdate();

#if 0
	// Turn GPIOB clock on
	bit_set(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);

	// Set B2 as Input Mode Floating
	bit_clear(GPIOB->CRL, GPIO_CRL_MODE2);
	bit_set(GPIOB->CRL, GPIO_CRL_CNF2_0);
	bit_clear(GPIOB->CRL, GPIO_CRL_CNF2_1);
#endif

#if 0
	//LED GPIO Init
	RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
	GPIOE->CRL &= ~(GPIO_CRL_CNF6 + GPIO_CRL_MODE6);
	GPIOE->CRL |= GPIO_CRL_MODE6_0;
	GPIOE->BSRR |= GPIO_BSRR_BS6;
#endif

#if 0
	// If B2 (BOOT1) is HIGH then go into HID bootloader...
	if(GPIOB->IDR & GPIO_IDR_IDR2) {
#endif
		USB_Init(HIDUSB_EPHandler, HIDUSB_Reset);
#if 0
	} else {
		// Turn GPIOB clock off
		bit_clear(RCC->APB2ENR, RCC_APB2ENR_IOPBEN);

		SCB->VTOR = USER_PROGRAM;

		__asm__ volatile(
			"msr msp, %0\n"
			"bx %1\n"
			:: "r" (usrSp), "r" (usrMain));
	}
#endif

#if 1
	GPIOA->CRH &= ~(GPIO_CRH_CNF10 + GPIO_CRH_MODE10);
	GPIOA->CRH |= GPIO_CRH_MODE10_0;
	GPIOA->BSRR |= GPIO_BSRR_BS10;
#endif

#if 0
	while (1)
	{
		GPIOE->BSRR |= GPIO_BSRR_BS6;
		delay(500);

		GPIOE->BSRR |= GPIO_BSRR_BR6;
		delay(500);
	}
#endif

	for(;;);
}
