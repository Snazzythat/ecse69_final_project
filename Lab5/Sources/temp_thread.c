////////////////////////////////////////////////////////////////////////////////
//	File Name				: temp_thread.c
//	Description			: program entry 
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////
	
//	Includes
#include "main.h"

//	Globals
osThreadId temp_thread_ID;
osThreadDef(temp_thread, osPriorityNormal, 1,0);

/*
** Brief:			Starts the temperature sensor thread in the OS (from Inactive into the Lifecycle)
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void temp_thread_init(void *args)
{
	temp_thread_ID = osThreadCreate(osThread(temp_thread), args);
}

/*
** Brief:			The temperature sensor thread function in the OS
**						Waits for a signal from the TIM4 interrupt handler and then 
**						toggles the on board LEDs
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void temp_thread(void const *args)
{
	while(1)
	{
		osSignalWait(0x00000001, osWaitForever);
		temperature = temp_adc_conversion();
	}
}
