#ifndef MYDRIVER_INC_RINGBUFFER_H_
#define MYDRIVER_INC_RINGBUFFER_H_


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct
{
	unsigned char *pBuffer ;
	uint32_t writePoint;
	uint32_t readPoint;
	uint16_t  length;

}RingBuffer_t;


void RingBuffer_Init(RingBuffer_t *pRingBuffer , uint8_t *Buffer , uint16_t length);
bool RingBuffer_Is_Empty(RingBuffer_t *pRingBuffer);
bool RingBuffer_Is_Fully(RingBuffer_t *pRingBuffer);
bool RingBuffer_Add(RingBuffer_t *pRingBuffer , unsigned char ch);
int RingBuffer_Subtract(RingBuffer_t *pRingBuffer);
void Ring_Buffer_Clear(RingBuffer_t *pRingBuffer);















#endif /* MYDRIVER_INC_RINGBUFFER_H_ */
