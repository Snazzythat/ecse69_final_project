////////////////////////////////////////////////////////////////////////////////
//	File Name				: transceiver_thread.c
//	Description			: program entry 
//	Author					: Team 12
//	Date						: Nov 29th, 2016
////////////////////////////////////////////////////////////////////////////////

// Includes
#include "main.h"

// Globals
int connected = 1;
osThreadId transceiver_thread_ID;
osThreadDef(transceiver_thread, osPriorityNormal, 1,0);

/*
** Brief:			Starts the display thread in the OS (from Inactive into the Lifecycle)
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void transceiver_thread_init(void *args)
{
	transceiver_thread_ID = osThreadCreate(osThread(transceiver_thread), args);
}

/*
** Brief:			The display thread function in the OS
**						Waits for a signal from the TIM4 interrupt handler and then 
**						toggles the on board LEDs
** Params:		A void pointer to initial arguments, NULL if unused
** Return:		None
*/
void transceiver_thread(void const *args)
{
	int len = 4, flushed;
	uint8_t temp[4]; //= {0x09, 0x01, 0xfa, 0x02, 0x02, 0x90};
//	uint8_t temp2 = 0x00;
//	uint8_t temp3 = 0x10;
//	
//	uint8_t state;
//	uint8_t byte;
	
	while(1)
	{
		osSignalWait(0x00000001, osWaitForever);
		
		/////////////////////////////////////////////////RECEIVING
		flushed = burst_receive(temp, len);
		if (flushed)
			printf("Was flushed.\n");
	
//	CC2500_read_one(CC2500_SIDLE);
//	state = CC2500_get_state();
//	printf("State: %x\n", state);
//	if (state == 1)
//	{
//		CC2500_read_one(CC2500_SRX);
//		byte = CC2500_get_rxbytes();
//		printf("# Bytes: %x\n", byte);
//		state = CC2500_get_state();
//		printf("State: %x\n", state);
//		if (byte == len)
//		{
//			CC2500_Read(temp, CC2500_RX_FIFO_BURST, len);
//			for (int i = 0; i < len; i++)
//			{
//				printf("Packet %d: %x\n", i, temp[i]);
//			}
//		}
//		else if (byte > 0)
//		{
//			CC2500_flush_rx();
//			//printf("Flushed.\n");
//		}
//	}
//	else
//	{
//		printf("Not IDLE.\n");
//	}

		/////////////////////////////////////////////////SENDING

//		CC2500_flush_tx();
//		CC2500_read_one(CC2500_SIDLE);
//		temp2 = CC2500_get_state();
//		
//		if (temp2 == 1){
//		CC2500_write_tx(temp, 6);
//		CC2500_read_one(CC2500_STX);
//		}else{
//			printf("NOT IN IDDLE");
//		}
	}
}
