////////////////////////////////////////////////////////////////////////////////
//	File Name				: transceiver_protocol.h
//	Description			: program header 
//	Author					: Team 12
//	Date						: Nov 29th, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _TRANSCEIVER_PROTOCOL_H
#define _TRANSCEIVER_PROTOCOL_H

//	Exported Functions
void transmit_ack(void);
int transmit_comfirm(uint8_t);
void byte_transmit(uint8_t);
void burst_transmit(uint8_t*, int);
uint8_t byte_receive(void);
int burst_receive(uint8_t *, int);

#endif	/*_TRANSCEIVER_PROTOCOL_H*/
