////////////////////////////////////////////////////////////////////////////////
//	File Name				: led_thread.c
//	Description			: program entry 
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////
	
//	Includes
#include "main.h"

//	Globals
osThreadId led_thread_ID;
osThreadDef(led_thread, osPriorityNormal, 1,0);

/*
** Brief:			Starts the LED thread in the OS (from Inactive into the Lifecycle)
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void led_thread_init(void *args)
{
	led_thread_ID = osThreadCreate(osThread(led_thread), args);
}

/*
** Brief:			The LED thread function in the OS
**						Waits for a signal from the TIM interrupt handler and then 
**						toggles the on board LEDs
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void led_thread(void const *args)
{
	while(1)
	{
		osSignalWait(0x00000001, osWaitForever);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
	}
}
