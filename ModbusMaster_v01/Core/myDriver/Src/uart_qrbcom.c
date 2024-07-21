/*
 * uart_qrbcom.c
 *
 *  Created on: Jun 30, 2024
 *      Author: omer
 */

#include "uart_qrbcom.h"

RingBuffer_t	usart2_InRb;
uint8_t			usart2_inRingBuffer[BUFF_SIZE];

RingBuffer_t	usart2_OutRb;
uint8_t			usart2_outRingBuffer[BUFF_SIZE];


Uart_Comm_t		uartComm;

extern UART_HandleTypeDef huart2;

void UARTx_CellCommInit(void)
{

	//Ring Buffer Start
	RingBuffer_Init(&usart2_InRb, usart2_inRingBuffer, BUFF_SIZE);
	RingBuffer_Init(&usart2_OutRb, usart2_outRingBuffer, BUFF_SIZE);
	//Uart Start
	uartComm.huart = &huart2;
	uartComm.ringBufferIn = &usart2_InRb;
	uartComm.ringBufferOut = &usart2_OutRb;

	UARTx_Init(&uartComm);

	__HAL_UART_ENABLE_IT(uartComm.huart,UART_IT_RXNE);

}

#define PRINT_BUFF_SIZE					256
char    printBuffer[PRINT_BUFF_SIZE];
va_list arg;



int UARTx_Printf(const char *format , ...)
{
	int status;

	va_start(arg,format);
	status = vsnprintf(printBuffer,PRINT_BUFF_SIZE,format,arg);
	va_end(arg);

	UARTx_WriteString(&uartComm, printBuffer);

	return status;

}

