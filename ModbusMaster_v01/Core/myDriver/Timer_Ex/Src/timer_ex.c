#include "timer_ex.h"

extern uint32_t msTick;


void Tick_Timer_Init(Tick_Time_t *time , uint32_t intervalMs)
{

	Tick_Timer_Set_Time(time , intervalMs);

}


void Tick_Timer_Set_Time(Tick_Time_t *time , uint32_t intervalMs)
{

	time->activated = true;
	time->interval = intervalMs;
	time->startTick = msTick;

}

void Tick_Timer_Stop_Time(Tick_Time_t *time)
{

	time->activated = false;

}

bool Tick_Timer_Check_Elapsed_Time(Tick_Time_t *time)
{
	uint32_t currentTick;

	if(time->activated)
	{
		currentTick = msTick;

		if (time->startTick <= currentTick)
		{
			if(currentTick - time->startTick >= time->interval)
			{
				time->activated = false;
				return true;
			}

		}
		else
		{
			if((0xFFFFFFFF - (time->startTick - currentTick)) >= time->interval)
			{
				time->activated = false;
				return true;
			}

		}
	}

	return false;

}
