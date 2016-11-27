////////////////////////////////////////////////////////////////////////////////
//	File Name				: accelerometer.h
//	Description			: program header
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H

// INCLUDE
#include "arm_math.h"

// STRUCT INITIALIZATION
typedef struct
{
	float X;
	float Y;
	float Z;
} TM_LIS302DL_t;

// PROTOTYPES
void acc_init(void);
void acc_read(void);
float acc_roll(void);
float acc_pitch(void);

#endif /*_ACCELEROMETER_H*/
