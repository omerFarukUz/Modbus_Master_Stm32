#ifndef MYDRIVER_INC_UART_EX_H_
#define MYDRIVER_INC_UART_EX_H_

#include <main.h>
#include "RingBuffer.h"


#define UART_TX_IT					0x01 << 7
#define UART_TX_EMPTY				0x01 << 7


typedef struct
{

	UART_HandleTypeDef		*huart;
	RingBuffer_t			*ringBufferIn;
	RingBuffer_t			*ringBufferOut;

}Uart_Comm_t;

void UARTx_Init(Uart_Comm_t *uart);
void UARTx_WriteSingleChar(Uart_Comm_t *uart ,char ch);
void UARTx_WriteString(Uart_Comm_t *uart ,char *str);


#endif /* MYDRIVER_INC_UART_EX_H_ */
