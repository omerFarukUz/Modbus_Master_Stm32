#include "uart_ex.h"


extern UART_HandleTypeDef	huart2;
RingBuffer_t				*usart2In;
RingBuffer_t				*usart2Out;



void UARTx_Init(Uart_Comm_t *uart)
{
	if (uart->huart == &huart2)
	{
		usart2In = uart->ringBufferIn;
		usart2Out = uart->ringBufferOut;
	}

}


void UARTx_WriteSingleChar(Uart_Comm_t *uart ,char ch)
{

	if (RingBuffer_Is_Fully(uart->ringBufferOut))
	{
		if (!(uart->huart->Instance->CR1 == UART_TX_IT))
		{
			HAL_UART_Transmit_IT(&huart2, (uint8_t*)RingBuffer_Subtract(uart->ringBufferOut), 1);
		}
		while(RingBuffer_Is_Fully(uart->ringBufferOut));
	}

	RingBuffer_Add(uart->ringBufferOut, ch);

}

void UARTx_WriteString(Uart_Comm_t *uart ,char *str)
{
	int check;
	char *ptr;
	ptr = str;

	while(*ptr)
	{
		UARTx_WriteSingleChar(uart, *ptr);
		ptr++;
	}

	if(!(uart->huart->Instance->CR1 & UART_TX_IT))
	{
		check = RingBuffer_Subtract(uart->ringBufferOut);

		if(check > -1)
		{
			uart->huart->Instance->DR = (uint8_t)(check & 0xFF);
			__HAL_UART_ENABLE_IT(uart->huart,UART_IT_TXE);
		}

	}

}

