/*
 * RingBuffer.c
 *
 *  Created on: Jun 29, 2024
 *      Author: omer
 */

#include "RingBuffer.h"



void RingBuffer_Init(RingBuffer_t *pRingBuffer , uint8_t *Buffer , uint16_t length)
{
	pRingBuffer->writePoint = 0;
	pRingBuffer->readPoint  = 0;
	pRingBuffer->pBuffer    = Buffer;
	pRingBuffer->length		= length;

}


bool RingBuffer_Is_Empty(RingBuffer_t *pRingBuffer)
{

	return(pRingBuffer->writePoint == pRingBuffer->readPoint) ? true : false;
}

bool RingBuffer_Is_Fully(RingBuffer_t *pRingBuffer)
{
	int div = (pRingBuffer->writePoint - pRingBuffer->readPoint);

	if(div < 0) div = pRingBuffer->length + div;

	return(div == (pRingBuffer->length - 1)) ? true : false;
}

bool RingBuffer_Add(RingBuffer_t *pRingBuffer , unsigned char ch)
{
	bool retVal = false;

	if(!RingBuffer_Is_Fully(pRingBuffer))
	{
		pRingBuffer->pBuffer[pRingBuffer->writePoint] = ch;
		pRingBuffer->writePoint++;

		if(pRingBuffer->writePoint == pRingBuffer->length) pRingBuffer->writePoint = 0;

		retVal = true;

	}

	return retVal;
}

int RingBuffer_Subtract(RingBuffer_t *pRingBuffer)
{
	int ch = -1;

	if (!RingBuffer_Is_Empty(pRingBuffer))
	{
		ch = pRingBuffer->pBuffer[pRingBuffer->readPoint];
		pRingBuffer->readPoint++;

		if(pRingBuffer->readPoint == pRingBuffer->length)
		{
			pRingBuffer->readPoint = 0;
		}
	}

	return ch;
}

void Ring_Buffer_Clear(RingBuffer_t *pRingBuffer)
{
	pRingBuffer->writePoint = 0;
	pRingBuffer->readPoint  = 0;

}

