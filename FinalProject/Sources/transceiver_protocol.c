////////////////////////////////////////////////////////////////////////////////
//	File Name				: transceiver_protocol.c
//	Description			: program entry 
//	Author					: Team 12
//	Date						: Nov 29th, 2016
////////////////////////////////////////////////////////////////////////////////

// Includes
#include "string.h"
#include "stdio.h"
#include "stdint.h"
#include "transceiver_protocol.h"
#include "cc2500.h"

/**
 * Send an ACK from one board to another
 * An ACK is simply a packet of 1 byte: 0xFF
 *
 * @param void
 *
 * @return void
 */
void transmit_ack(void)
{
	CC2500_flush_tx();
	CC2500_write_tx_one(0xFF);
}

/**
 * Comfirm that an ACK has been received
 *
 * @param uint8_t hex which is the ACK packet
 * received
 *
 * @return int 1 for confirmation, 0 for fail
 */
int transmit_comfirm(uint8_t hex)
{
	if (hex == 0xFF)
		return 1;
	return 0;
}

/////////////////////////////////////////////////SENDING

// Single byte transmission
void byte_transmit(uint8_t data)
{
	CC2500_flush_tx();
	CC2500_write_tx_one(data);
}

// Burst byte transmission
void burst_transmit(uint8_t *data, int len)
{
	uint8_t state;
	
	CC2500_flush_tx();
	CC2500_read_one(CC2500_SIDLE);
	state = CC2500_get_state();
	
	if (state == 1)
	{
		CC2500_write_tx(data, len);
		CC2500_read_one(CC2500_STX);
	}
}

/////////////////////////////////////////////////RECEIVING

// Single byte receiving
uint8_t byte_receive(void)
{
	uint8_t data;
	
	CC2500_read_one(CC2500_SRX);
	data = CC2500_read_rx_one();
	return data;
}

// Burst byte receiving, returns 1 if flushed
int burst_receive(uint8_t *data, int len)
{
	uint8_t state;
	uint8_t byte;
	
	CC2500_read_one(CC2500_SIDLE);
	state = CC2500_get_state();
	printf("State: %x\n", state);
	if (state == 1)
	{
		CC2500_read_one(CC2500_SRX);
		
		byte = CC2500_get_rxbytes();
		printf("# Bytes: %x\n", byte);
		if (byte == len)
		{
			CC2500_Read(data, CC2500_RX_FIFO_BURST, len);
			for (int i = 0; i < len; i++)
			{
				printf("Packet %d: %x\n", i, data[i]);
				state = CC2500_get_state();
				printf("State: %x\n", state);
			}
		}
		
		else if (byte > 0)
		{
			CC2500_flush_rx();
			printf("Flushed.\n");
			return 1;
		}
	}
	else
	{
		return 1;
		printf("Not IDLE.\n");
	}
	return 0;
}
