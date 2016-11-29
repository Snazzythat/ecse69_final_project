////////////////////////////////////////////////////////////////////////////////
//	File Name				: hardware_timer.c
//	Description			: program entry
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

// Includes
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "supporting_functions.h"
#include "hardware_timer.h"
#include "acc_thread.h"
#include "display_thread.h"

// Extern
extern osThreadId keypad_thread_ID, display_thread_ID, acc_thread_ID, temp_thread_ID;

// Iniialization of variables and structs
volatile int tim2_flag, tim3_flag, tim4_flag;
TIM_HandleTypeDef TIM_Handle3, TIM_Handle4, TIM_Handle2;

// INITIALIZE TIM3 
void tim3_init(void)
{
	__TIM3_CLK_ENABLE();
	
	// PERIOD*PRESCALAR CANNOT EXCEED 16BIT (TIM3)
	TIM_Handle3.Instance 								= TIM3;
	TIM_Handle3.Init.ClockDivision 			= 0;
	TIM_Handle3.Init.Prescaler 					= 4000;											// PRESCALAR OF 4000 (PRESCALAR OF 5999 - OLD)
	TIM_Handle3.Init.Period 						= 840;											// PERIOD OF 840 FOR 25HZ REFRESH RATE FOR ACCELEROMETER
	TIM_Handle3.Init.CounterMode 				= TIM_COUNTERMODE_UP;
	TIM_Handle3.Init.ClockDivision 			= TIM_CLOCKDIVISION_DIV1;
	TIM_Handle3.Init.RepetitionCounter 	= 0;
	
	if (HAL_TIM_Base_Init(&TIM_Handle3))
			Error_Handler(TIM_INIT_FAIL);
	HAL_TIM_Base_Start_IT(&TIM_Handle3);
		
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

// INITIALIZE TIM2
void tim2_init(void)
{
	__TIM2_CLK_ENABLE();
	
	// PERIOD*PRESCALAR CANNOT EXCEED 16BIT (TIM2)
	TIM_Handle2.Instance 									= TIM2;
	TIM_Handle2.Init.ClockDivision 				= 0;
	TIM_Handle2.Init.Prescaler 						= 25;												// PRESCALAR OF 25 (PRESCALAR OF 5999 - OLD)
	TIM_Handle2.Init.Period 							= 13999;										// PERIOD OF 13999 FOR 60HZ DISPLAY REFRESH RATE
	TIM_Handle2.Init.CounterMode 					= TIM_COUNTERMODE_UP;
	TIM_Handle2.Init.ClockDivision 				= TIM_CLOCKDIVISION_DIV1;
	TIM_Handle2.Init.RepetitionCounter 		= 0;
	
	if (HAL_TIM_Base_Init(&TIM_Handle2))
			Error_Handler(TIM_INIT_FAIL);
	HAL_TIM_Base_Start_IT(&TIM_Handle2);
		
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

// INITIALIZE TIM4
void tim4_init(void)
{
	__TIM4_CLK_ENABLE();
	
	// PERIOD*PRESCALAR CANNOT EXCEED 16BIT (TIM4)
	TIM_Handle4.Instance 								= TIM4;
	TIM_Handle4.Init.ClockDivision 			= 0;
	TIM_Handle4.Init.Prescaler 					= 8400;													// PRESCALAR OF 8400 (PRESCALAR OF 5999 - OLD)
	TIM_Handle4.Init.Period 						= 100;													// PERIOD OF 100 FOR 100HZ REFRESH RATE FOR ADC
	TIM_Handle4.Init.CounterMode 				= TIM_COUNTERMODE_UP;
	TIM_Handle4.Init.ClockDivision 			= TIM_CLOCKDIVISION_DIV1;
	TIM_Handle4.Init.RepetitionCounter 	= 0;
	
	if (HAL_TIM_Base_Init(&TIM_Handle4))
			Error_Handler(TIM_INIT_FAIL);
	HAL_TIM_Base_Start_IT(&TIM_Handle4);
		
	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

// SETS THE THREAD ACCORDING TO THE TIM USED //
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {	
	if(htim->Instance == TIM3)
		osSignalSet(keypad_thread_ID, 0x00000001);
	if(htim->Instance == TIM2)
		osSignalSet(display_thread_ID, 0x00000001);
	else if(htim->Instance == TIM4)
		osSignalSet(temp_thread_ID, 0x00000001);
}
