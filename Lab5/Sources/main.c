////////////////////////////////////////////////////////////////////////////////
//	File Name				: main.c
//	Description			: program entry
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

//	Includes
#include "main.h"


void init(void){
	  //	MCU Configuration: Reset of all peripherals, Initializes the Flash interface and the Systick
  HAL_Init();
	
  //	Configure the system clock
  SystemClock_Config();
	
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
//	acc_init();
//	keypad_col_init();
//	keypad_row_init();
}

/*
** Brief:	main program
**				
** Params:	None
** Return:	None
*/
int main(void)
{
	init();
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
	
	// Initialize wireless
	CC2500_Init();
	CC2500_Reset();
	
	uint8_t temp[32];
	uint8_t temp2 = 0x05;
	uint8_t temp3 = 0x10;

	while(1){
//		CC2500_Read(temp, 0x3f|0xC0, 32);
//		for (int i = 0; i<32; i++){
//		printf("Packet %d : %#02xz\n", i, temp[i]);
//		}
		
		/////////////////////////////////////////////////RECEIVING
		CC2500_read_one(CC2500_SRX);
		
		temp2 = CC2500_get_state();
		
		printf("SFM state:					%d\n", temp2);
		temp2 = CC2500_get_rxbytes();
				
		printf("TXBytes size:				%d\n", temp2);
		
		temp2 = CC2500_read_rx_one();
		
		printf("RX Bytes Read:			%d\n", temp2);
		
		
		/////////////////////////////////////////////////SENDING
//		temp2 = CC2500_get_state();
//		
//   	CC2500_read_one(CC2500_STX);
//		
//		printf("SFM state:\t\t%d\n", temp2);
//		
//		CC2500_write_tx_one(-9);
//		temp3 = CC2500_get_txbytes();
//		printf("SFM wrote to TX:\t%d\n", temp3);
//		CC2500_flush_tx();
		
	  osDelay(10);
	} 

	return 0;
}
