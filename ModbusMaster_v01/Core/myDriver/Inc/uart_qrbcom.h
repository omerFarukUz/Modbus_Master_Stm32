#ifndef MYDRIVER_INC_UART_QRBCOM_H_
#define MYDRIVER_INC_UART_QRBCOM_H_

#include "uart_ex.h"

#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"


#define BUFF_SIZE					1024

void UARTx_CellCommInit(void);
int UARTx_Printf(const char *format , ...);

#endif /* MYDRIVER_INC_UART_QRBCOM_H_ */
