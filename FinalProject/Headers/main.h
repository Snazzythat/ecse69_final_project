////////////////////////////////////////////////////////////////////////////////
//	File Name				: main.h
//	Description			: header file for main.c
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _MAIN_H
#define _MAIN_H

// INCLUDES
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "sysclk_config.h"
#include "supporting_functions.h"
#include "display.h"
#include "transceiver_protocol.h"
#include "cc2500.h"
#include "hardware_timer.h"
#include "display_thread.h"
#include "led_thread.h"
#include "transceiver_thread.h"
//#include "accelerometer.h"
//#include "lis3dsh.h"
//#include "keypad_thread.h"
//#include "temp_thread.h"
//#include "keypad.h"
//#include "acc_thread.h"
//#include "temperature_sensor.h"
//#include "kalman_filter.h"

// EXTERN
extern int display_counter;
extern TIM_HandleTypeDef TIM_Handle2, TIM_Handle3, TIM_Handle4;
//extern TM_LIS302DL_t axis_data_struct;
//extern float acc_lis3dsh, temperature;
//extern char now;
//extern int alarm_counter, display_flag;

//// DEFINE
//#define ALARM 35

#endif /*_MAIN_H*/
