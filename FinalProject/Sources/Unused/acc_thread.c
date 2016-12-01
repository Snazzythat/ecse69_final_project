////////////////////////////////////////////////////////////////////////////////
//	File Name				: acc_thread.c
//	Description			: program entry 
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

//	Includes
#include "main.h"

//	Globals
osThreadId acc_thread_ID;
osThreadDef(acc_thread, osPriorityNormal, 1,0);

/*
** Brief:			Starts the accelerometer thread in the OS (from Inactive into the Lifecycle)
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void acc_thread_init(void *args)
{
	acc_thread_ID = osThreadCreate(osThread(acc_thread), args);
}

/*
** Brief:			The accelerometer thread function in the OS
**						Waits for a signal from the EXTI0 interrupt handler and then 
**						toggles the on board LEDs
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void acc_thread(void const *args)
{
	while(1)
	{
		osSignalWait(0x00000001, osWaitForever);
		acc_read();
	}
}
