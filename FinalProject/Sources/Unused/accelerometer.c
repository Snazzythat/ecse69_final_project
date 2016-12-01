////////////////////////////////////////////////////////////////////////////////
//	File Name				: accelerometer.c	
//	Description			: program entry	
//	Author					: Team 12	
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "LIS3DSH.h"
#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "accelerometer.h"
#include "kalman_filter.h"

extern osThreadId acc_thread_ID;

// VARIABLES AND STRUCTS DECLARATION
float temp1, temp2, angle, acc_lis3dsh, x, y, z, filtered_x, filtered_y, filtered_z;
int roll = 0, pitch = 0;
uint8_t buffer[6];
kalmanstruct xks, yks, zks;

// STRUCT INITIALIZE
LIS3DSH_InitTypeDef acc_LIS3DSH_struct;
LIS3DSH_DRYInterruptConfigTypeDef acc_LIS3DSH_DRYInterruptConfig_struct;
GPIO_InitTypeDef acc_GPIO_struct;
TM_LIS302DL_t axis_data_struct;

// SETTING UP THE ACCELEROMETER AND PASSING THE INITIAL SETING
// WE ALSO SET THE INT1 PIN LOCATED ON GPIOE GPIO_PIN_0 USED FOR INTERRUPTS
void acc_init(void)
{
	acc_LIS3DSH_struct.Power_Mode_Output_DataRate 								= LIS3DSH_DATARATE_25; // 25 HZ
	acc_LIS3DSH_struct.Axes_Enable 																= LIS3DSH_XYZ_ENABLE;
	acc_LIS3DSH_struct.Continous_Update 													= LIS3DSH_ContinousUpdate_Disabled;
	acc_LIS3DSH_struct.Full_Scale 																= LIS3DSH_FULLSCALE_2;
	acc_LIS3DSH_struct.AA_Filter_BW 															= LIS3DSH_AA_BW_50;
	acc_LIS3DSH_struct.Self_Test 																	= LIS3DSH_SELFTEST_NORMAL;

	acc_LIS3DSH_DRYInterruptConfig_struct.Dataready_Interrupt 		= LIS3DSH_DATA_READY_INTERRUPT_ENABLED;
	acc_LIS3DSH_DRYInterruptConfig_struct.Interrupt_signal 				= LIS3DSH_ACTIVE_HIGH_INTERRUPT_SIGNAL;
	acc_LIS3DSH_DRYInterruptConfig_struct.Interrupt_type 					= LIS3DSH_INTERRUPT_REQUEST_PULSED; 

	LIS3DSH_Init(&acc_LIS3DSH_struct);
	LIS3DSH_DataReadyInterruptConfig(&acc_LIS3DSH_DRYInterruptConfig_struct);

	// GPIO initialisation
	__HAL_RCC_GPIOE_CLK_ENABLE();
	acc_GPIO_struct.Pin 																					= GPIO_PIN_0;
	acc_GPIO_struct.Mode 																					= GPIO_MODE_IT_RISING;
	acc_GPIO_struct.Speed 																				= GPIO_SPEED_FREQ_VERY_HIGH;
	acc_GPIO_struct.Pull 																					= GPIO_NOPULL;

	HAL_GPIO_Init (GPIOE, &acc_GPIO_struct);

	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	HAL_NVIC_SetPriority(EXTI0_IRQn,1,1);
	
	// Structs initialization: q, r, x, p, k, f, h
	kalman_struct_init(&xks, 0.77212, 5, 0, 1, 0, 1, 1);
	kalman_struct_init(&yks, 1.19949, 3, 0, 1, 0, 1, 1);
	kalman_struct_init(&zks, 1.80848, 5, 0, 1, 0, 1, 1);
}

// READ AXIS FUNCTION
/*
** BECAUSE LIS3DSH ONLY OUTPUTS ACCELERATION OF THE AXIS
** X, Y AND Z INTO TWO 8 BITS (HIGH SIDE AND LOW SIDE). AS
** SUCH, WE SHIFT THE LOW SIDE BY 8 BIT THEN OR THE HIGH
** SIDE TO CREAT THE 16 BITS TO READ THE VALUE.
*/
void acc_read(void)
{
	//READING VALUES
	LIS3DSH_Read(&buffer[0], LIS3DSH_OUT_X_L, 1);
	LIS3DSH_Read(&buffer[1], LIS3DSH_OUT_X_H, 1);
	LIS3DSH_Read(&buffer[2], LIS3DSH_OUT_Y_L, 1);
	LIS3DSH_Read(&buffer[3], LIS3DSH_OUT_Y_H, 1);
	LIS3DSH_Read(&buffer[4], LIS3DSH_OUT_Z_L, 1);
	LIS3DSH_Read(&buffer[5], LIS3DSH_OUT_Z_H, 1);

	x = (int16_t)((buffer[1] << 8) + buffer[0])*LIS3DSH_SENSITIVITY_2G;
	y = (int16_t)((buffer[3] << 8) + buffer[2])*LIS3DSH_SENSITIVITY_2G;
	z = (int16_t)((buffer[5] << 8) + buffer[4])*LIS3DSH_SENSITIVITY_2G;
	
	kalmanfilter(&x, &filtered_x, 1, &xks);
	kalmanfilter(&y, &filtered_y, 1, &yks);
	kalmanfilter(&z, &filtered_z, 1, &zks);

	axis_data_struct.X = (filtered_x*(float)9.9244e-4)+(filtered_y*(float)-2.2917e-5)+(filtered_z*(float)-8.7305e-6)+(float)0.0033;
	axis_data_struct.Y = (filtered_x*(float)-1.3697e-5)+(filtered_y*(float)9.7494e-4)+(filtered_z*(float)8.9608e-7)-(float)0.0097;
	axis_data_struct.Z = (filtered_x*(float)1.3806e-5)+(filtered_y*(float)-1.5268e-5)+(filtered_z*(float)9.4835e-4)-(float)0.0439;
}

// ROLL FUNCTION TO FIND THE ROLL ANGLE
float acc_roll(void)
{
	temp1 = pow(axis_data_struct.Y, 2) + pow(axis_data_struct.Z, 2);
	temp2 = axis_data_struct.X / sqrt(temp1);
	angle = atan(temp2);

	return angle*180.0f/3.14159f + 90.0f;
}

// PITCH FUNCTION TO FIND THE PITCH ANGLE
float acc_pitch(void)
{
	temp1 = pow(axis_data_struct.X, 2) + pow(axis_data_struct.Z, 2);
	temp2 = axis_data_struct.Y / sqrt(temp1);
	angle = atan(temp2);

	return angle*180.0f/3.14159f + 90.0f;
}

// EXTI CALLBACK FUNCTION, CALLED EVERY TIME THE IRQHANDLER IS CALLED
void HAL_GPIO_EXTI_Callback(uint16_t Gpio_Pin)
{
	if (Gpio_Pin == GPIO_PIN_0)
		osSignalSet(acc_thread_ID, 0x00000001);
}
