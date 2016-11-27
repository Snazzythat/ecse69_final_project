////////////////////////////////////////////////////////////////////////////////
//	File Name				: main.c
//	Description			: program entry
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

//	Includes
#include "main.h"

/*
** Brief:	main program
**				
** Params:	None
** Return:	None
*/
int main(void)
{
  //	MCU Configuration: Reset of all peripherals, Initializes the Flash interface and the Systick
   HAL_Init();
	
  //	Configure the system clock
  SystemClock_Config();

  CC2500_Init();
	
//	//	System initialization
//	tim2_init();
//	tim3_init();
//	tim4_init();
//	
//	// Display initialization
//	rgb_led_init();
//	gpio_led_init();
//	segment_display_init();
//	segment_segments_init();
//	
//	// I/O initialization
//	temp_adc_init();
	acc_init();
//	keypad_col_init();
//	keypad_row_init();
//	
//	// Initialize the OS
//	osKernelInitialize();
//	
//	// Thread initialization
//	display_thread_init(NULL);
//	temp_thread_init(NULL);
//	keypad_thread_init(NULL);
//	acc_thread_init(NULL);
////	led_thread_init(NULL);
//		
//	// Start threads
//	osKernelStart();
//	osDelay(osWaitForever);

	while(1)
	{
		printf("mothafuckin part num: %d" ,CC2500_get_part_num());
		acc_read();
	}
  
  return 0;
}
