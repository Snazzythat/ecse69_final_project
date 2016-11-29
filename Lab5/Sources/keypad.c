////////////////////////////////////////////////////////////////////////////////
//	File Name				: keypad.c
//	Description			: program entry
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "stm32f4xx_hal.h"
#include "keypad.h"

// STRUCT INITIALIZATION
GPIO_InitTypeDef GPIO_InitStructure_col;
GPIO_InitTypeDef GPIO_InitStructure_row;

// VARIABLES INITIALIZATION
int display_flag = 3;
char prev = '\0', now = '\0';

/*
**INITALISE THE GPIO CLK AND PIN
**TO READ THE COLUMN OUTPUT AS THE 
**ROW IS FILLED THROUGH
*/
void keypad_col_init(void)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	GPIO_InitStructure_col.Pin 			= GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStructure_col.Mode 		= GPIO_MODE_INPUT;
	GPIO_InitStructure_col.Speed 		= GPIO_SPEED_HIGH;
	GPIO_InitStructure_col.Pull 		= GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure_col);
}

/* 
**INITIALISE THE GPIO AND PIN
**FOR THE ROW. THE ROW PINS IS
**SET HIGH AS IT FILTERS THROUGH
**EACH ROW. AS EACH ROW IS SET ONE
**ONE AT A TIME SO THAT WE ARE ABLE
**READ WHICH COLUMN WAS PUSHED
*/
void keypad_row_init(void)
{
	__HAL_RCC_GPIOE_CLK_ENABLE();
	
	GPIO_InitStructure_row.Pin 			= GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
	GPIO_InitStructure_row.Mode 		= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure_row.Speed 		= GPIO_SPEED_HIGH;
	GPIO_InitStructure_row.Pull 		= GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStructure_row);
}

// IF REGISTER FUNCTION TO CHEK ON KEYPAD REGISTRATION CONDITION
void keypad_input(void)
{
	if(prev == '\0')
	{
		now = keypad_sweep();
		prev = now;
	}
	else
	{
		now = '\0';
		prev = keypad_sweep();
	}
	
	// SETTING DISPLAY FLAGS DEPENDING OF ALPHABETICAL KEYS PRESSED
	if(now == 'c')
		display_flag = 0; // FOR PIEZOMETER
	else if(now == 'a')
		display_flag = 1; // FOR ROLL
	else if(now == 'b')
		display_flag = 2; // FOR PITCH
	else if(now == 'd')
		display_flag = 3; // FOR INPUT
}

/*
**THIS FUNCTION CYCLES THROUGH THE ROW AND CHECKS
**WHICH COLUMN IS ON DEPENDING ON WHICH ROW
**WAS SET HIGH
*/
char keypad_sweep(void)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1)
	{
		return '1';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1)
	{
		return '2';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
	{
		return '3';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1)
	{
		return 'a';
	}
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1)
	{
		return '4';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1)
	{
		return '5';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
	{
		return '6';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1)
	{
		return 'b';
	}
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1)
	{
		return '7';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1)
	{
		return '8';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
	{
		return '9';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1)
	{
		return 'c';
	}
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0) == 1)
	{
		return '*';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == 1)
	{
		return '0';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2) == 1)
	{  
		return '#';
	} 
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3) == 1)
	{
		return 'd';
	}
	// SETS CHAR TO NUL BY DEFAULT
	return '\0';
}
