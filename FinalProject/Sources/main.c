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
	
	// Initialize wireless components
	CC2500_Init();
	CC2500_Reset();
	
	//	System initialization
	tim2_init();
	tim3_init();
	tim4_init();
	
	// Display initialization
	rgb_led_init();
	gpio_led_init();
	segment_display_init();
//	segment_segments_init();
	
//	// I/O initialization
//	acc_init();
//	temp_adc_init();
//	keypad_col_init();
//	keypad_row_init();
	
	// Initialize the OS
	osKernelInitialize();
	
	// Thread initialization
	display_thread_init(NULL);
	transceiver_thread_init(NULL);
	led_thread_init(NULL);
////	temp_thread_init(NULL);
////	keypad_thread_init(NULL);
////	acc_thread_init(NULL);
		
	// Start threads
	osKernelStart();
	osDelay(osWaitForever);

//	uint8_t temp2 = 0x00;
//	
//	while(1)
//	{
//				CC2500_read_one(CC2500_SRX);
//		
//		temp2 = CC2500_get_state();
//		
//		printf("SFM state:					%d\n", temp2);
//		temp2 = CC2500_get_rxbytes();
//				
//		printf("RXBytes size:				%d\n", temp2);
//		
//		temp2 = CC2500_read_rx_one();
//		
//		printf("RX Bytes Read:			%d\n", temp2);
//		
//		osDelay(100);
//	} 
	return 0;
}
