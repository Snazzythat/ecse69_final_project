////////////////////////////////////////////////////////////////////////////////
//	File Name				: main.h
//	Description			: header file for main.c
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H
#define _MAIN_H

// INCLUDES
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "sysclk_config.h"
#include "supporting_functions.h"
#include "lis3dsh.h"
#include "accelerometer.h"
#include "display.h"
#include "temperature_sensor.h"
#include "kalman_filter.h"
#include "hardware_timer.h"
#include "keypad.h"
#include "acc_thread.h"
#include "display_thread.h"
#include "keypad_thread.h"
#include "temp_thread.h"
#include "led_thread.h"
#include "cc2500.h"

// EXTERN
extern int display_counter, alarm_counter, display_flag;
extern float acc_lis3dsh, temperature;
extern char now;
extern TIM_HandleTypeDef TIM_Handle2, TIM_Handle3, TIM_Handle4;
extern TM_LIS302DL_t axis_data_struct;
void init(void);

// DEFINE
#define ALARM 35

#endif /*_MAIN_H*/
