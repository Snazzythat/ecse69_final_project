////////////////////////////////////////////////////////////////////////////////
//	File Name				: kalman_filter.h	
//	Description			: program header
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _KALMAN_FILTER_H
#define _KALMAN_FILTER_H

// STRUCT DEFINE
typedef struct kalmanstruct
{
	float q;
	float r;
	float x;
	float p;
	float k;
	float f;
	float h;
}kalmanstruct;

// PROTOTYPE
void kalman_struct_init(kalmanstruct*, 	float, float, float, float, float, float, float);
void kalmanfilter(float*, float*, int, kalmanstruct*);

#endif /*_KALMAN_FILTER_H*/
