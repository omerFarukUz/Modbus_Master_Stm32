#ifndef MYDRIVER_TIMER_EX_INC_TIMER_EX_H_
#define MYDRIVER_TIMER_EX_INC_TIMER_EX_H_

#include <stdint.h>
#include <stdbool.h>


typedef struct
{
	uint32_t startTick;
	uint32_t interval;
	bool     activated;

}Tick_Time_t;

//// Init/////////////////
void Tick_Timer_Init(Tick_Time_t *time , uint32_t intervalMs);
//// Set/////////////////
void Tick_Timer_Set_Time(Tick_Time_t *time , uint32_t intervalMs);
//// Stop////////////////
void Tick_Timer_Stop_Time(Tick_Time_t *time);
//// Control Time///////
bool Tick_Timer_Check_Elapsed_Time(Tick_Time_t *time);



#endif /* MYDRIVER_TIMER_EX_INC_TIMER_EX_H_ */
