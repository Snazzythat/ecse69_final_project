////////////////////////////////////////////////////////////////////////////////
//	File Name				: keypad_thread.c
//	Description			: program entry 
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////
	
//	Includes
#include "main.h"

//	Globals
osThreadId keypad_thread_ID;
osThreadDef(keypad_thread, osPriorityNormal, 1,0);

/*
** Brief:			Starts the keypad thread in the OS (from Inactive into the Lifecycle)
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void keypad_thread_init(void *args)
{
	keypad_thread_ID = osThreadCreate(osThread(keypad_thread), args);
}

/*
** Brief:			The keypad thread function in the OS
**						Waits for a signal from the TIM3 interrupt handler and then 
**						toggles the on board LEDs
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void keypad_thread(void const *args)
{
	while(1)
	{
		osSignalWait(0x00000001, osWaitForever);
		keypad_input();
	}
}
