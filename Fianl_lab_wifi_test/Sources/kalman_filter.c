////////////////////////////////////////////////////////////////////////////////
//	File Name				: kalman_filter.c
//	Description			: program entry
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "kalman_filter.h"

// FILTER STRUCT INITIATION FUNCTION
void kalman_struct_init(kalmanstruct* kalmanstr, 	float q, float r, float x, float p, float k, float f, float h)
{
	kalmanstr->q = q;
	kalmanstr->r = r;
	kalmanstr->x = x;
	kalmanstr->p = p;
	kalmanstr->k = k;
	kalmanstr->f = f;
	kalmanstr->h = h;
}

// 1D KALMAN FILTER FUNTION: INTAKES INPUT_ARRAY, OUPUTS INTO FILTERED_ARRAY
void kalmanfilter(float* input_array, float* filtered_array, int array_len, kalmanstruct* kalmanstr)
{
	for (int i = 0; i < array_len; i++)
	{
		// PREDICT
		kalmanstr->x = kalmanstr->f * kalmanstr->x;
		kalmanstr->p = kalmanstr->f * kalmanstr->p * kalmanstr->f + kalmanstr->q;
		
		// UPDATE
		kalmanstr->k = (kalmanstr->p * kalmanstr->h) / (kalmanstr->h * kalmanstr->p * kalmanstr->h + kalmanstr->r);
		kalmanstr->p = (1 - kalmanstr->k * kalmanstr->h) * kalmanstr->p;
		kalmanstr->x = kalmanstr->x + kalmanstr->k * (input_array[i] - kalmanstr->h * kalmanstr->x);
		
		//OUTPUT
		filtered_array[i] = kalmanstr->x;
	}
}
