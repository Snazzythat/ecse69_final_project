////////////////////////////////////////////////////////////////////////////////
//	File Name				: keypad.h
//	Description			: program header
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _KEYPAD_H
#define _KEYPAD_H

// INCLUDE
#include <math.h>

// PROTOTYPES
void keypad_col_init(void);
void keypad_row_init(void);
void keypad_input(void);
char keypad_sweep(void);

#endif /*_KEYPAD_H*/
