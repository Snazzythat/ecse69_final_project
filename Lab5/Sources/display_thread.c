////////////////////////////////////////////////////////////////////////////////
//	File Name				: display_thread.c
//	Description			: program entry 
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////
	
//	Includes
#include "main.h"

// Extern
extern int button;

// Globals
osThreadId display_thread_ID;
osThreadDef(display_thread, osPriorityNormal, 1,0);

/*
** Brief:			Starts the display thread in the OS (from Inactive into the Lifecycle)
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void display_thread_init(void *args)
{
	display_thread_ID = osThreadCreate(osThread(display_thread), args);
}

/*
** Brief:			The display thread function in the OS
**						Waits for a signal from the TIM2 interrupt handler and then 
**						toggles the on board LEDs
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void display_thread(void const *args)
{
	while(1)
	{
		osSignalWait(0x00000001, osWaitForever);
		// Cyclign through displays
		display_cycling();
		blink_counter();
		
		// Check if dangerous temperature has been reached
		if (temperature < ALARM || (temperature >= ALARM && alarm_counter <= COUNTERALARM/2))
		{	//ALARM TEMPERATURE SETTING	
			// Chose what to display according to the dispaly flag
			if(display_flag == 0)
			{
				display(temperature, display_counter, display_flag);
			}
			else if(display_flag == 1)
			{
				display(acc_roll(), display_counter, display_flag);
			}
			else if(display_flag == 2)
			{
				display(acc_pitch(), display_counter, display_flag);
			}
			else if(display_flag == 3)
			{
				display(0, display_counter, display_flag);
			}
		}
		else //	Toggling between display on and display off half the time
		{
			display(0, -1, display_flag);
		}
	}
}
