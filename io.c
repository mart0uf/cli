/*
*******************************************************************************
@file	io.c
@brief	A file for receiving and sending symbols for the console.
*******************************************************************************
@attention

The MIT License

Copyright (c) 2024 Martouf (Kolegov A.A.)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************
*/

#include "io.h"
#include "opt.h"

/* For HAL STM32 */
#if (CLI_FOR_STM32_HAL == TRUE)
#include "main.h"
#include "usart.h"
/* Parameter */
#define CLI_UART huart1

int __io_cli_putchar(int ch) {
	HAL_UART_Transmit(&CLI_UART, (uint8_t*)&ch, 1, 300);
	return 0;

}

int __io_cli_getchar(void) {
	int ch = 0;
	HAL_UART_Receive(&CLI_UART, (uint8_t*)&ch, 1, 0);
	return ch;
}

#endif

/* For CMSIS STM32 */
#if (CLI_FOR_STM32_CMSIS == TRUE)
#include "main.h"
#define CLI_UART USART1
int __io_cli_putchar(int ch) {
	while(1) {
		if (READ_BIT(CLI_UART->CR1, USART_CR1_TE)) {
			if ((CLI_UART->ISR & UART_FLAG_TXE)) {
				CLI_UART->TDR = ch;
				return 0;
			}
		}
	}
	return 0;

}

int __io_cli_getchar(void) {
	int ch = 0;
	if (READ_BIT(CLI_UART->CR1, USART_CR1_RE)) {
		if ((CLI_UART->ISR & USART_ISR_RXNE)) {
			ch = (int)CLI_UART->RDR;
		}
	}
	return ch;
}
#endif

/* For ZYNQ  */
#if (CLI_FOR_ZYNQ == TRUE)
#include "xuartps_hw.h"
XUartPs_Config *Config_UART;
XUartPs UART_PS;
u32 BaseAddress = SHELL_STDIO_BASEADDRESS;

int __io_cli_putchar(int ch) {
	while (XUartPs_IsTransmitFull(BaseAddress));
	/* Write the byte into the TX FIFO */
	XUartPs_WriteReg(BaseAddress, XUARTPS_FIFO_OFFSET, (u32)sb);
	return 0;

}

int __io_cli_getchar(void) {
	u32 RecievedByte = 0;
	/* Wait until there is data */
	if (XUartPs_IsReceiveData(BaseAddress)) {
		RecievedByte = XUartPs_ReadReg(BaseAddress, XUARTPS_FIFO_OFFSET);
	}
	/* Return the byte received */
	return (int)RecievedByte;
}
#endif
