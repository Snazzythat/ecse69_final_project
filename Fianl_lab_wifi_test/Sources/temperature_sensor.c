////////////////////////////////////////////////////////////////////////////////
//	File Name				: temperature_sensor.c
//	Description			: program entry
//	Author					: Team 12	
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

//	Includes
#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "kalman_filter.h"
#include "temperature_sensor.h"

//	Global variables
ADC_HandleTypeDef temp_ADC_Handle;																					// definition of ADC1 handle struct
ADC_InitTypeDef temp_ADC_Init; 																							// definition of ADC1 initialiation struct
ADC_ChannelConfTypeDef temp_ADC_Channel;																		// definition of ADC1 channel struct
ADC_MultiModeTypeDef temp_ADC_Mode; 																				// define ADC1 mode struct
HAL_LockTypeDef temp_ADC_Lock; 																							// define ADC1 locking object
GPIO_InitTypeDef GPIO_InitDef;
kalmanstruct vks;
float temperature = 0;

/*
**Brief: Sets up the desired(refer to header) ADC and corresponding GPIO for input
**Params: None
**Return: None
*/
void temp_adc_init(void)
{	
	//  Initialize ADC init struct
	temp_ADC_Init.ClockPrescaler 								= ADC_CLOCK_SYNC_PCLK_DIV4;			// ADC Clock frequency 42MHz (168/4)
	temp_ADC_Init.Resolution 										= ADC_RESOLUTION_12B;						// 12 bit resolution, better but slower
	temp_ADC_Init.DataAlign 										= ADC_DATAALIGN_RIGHT;					// align the 12 bits data at the right of the 32 bits words
	temp_ADC_Init.ScanConvMode 									= DISABLE;											// single channel mode
	temp_ADC_Init.EOCSelection 									= ADC_EOC_SEQ_CONV;							// perform ADC conversions without having to read all conversion data
	temp_ADC_Init.ContinuousConvMode 						= DISABLE;											// single mode convertion
	temp_ADC_Init.DMAContinuousRequests 				= DISABLE;											// single mode DMA request
	temp_ADC_Init.NbrOfConversion 							= 1;														// one conversion
	temp_ADC_Init.DiscontinuousConvMode					= ENABLE;												// enable discountinuous mode
	temp_ADC_Init.NbrOfDiscConversion 					= 1;														// one conversion
	temp_ADC_Init.ExternalTrigConv 							= ADC_SOFTWARE_START;						// no external trigger
	temp_ADC_Init.ExternalTrigConvEdge 					= ADC_SOFTWARE_START;						// no external trigger
	
	// Initialize ADC handle struct
	temp_ADC_Handle.Instance 										= TEMP_ADC;
	temp_ADC_Handle.Init 												= temp_ADC_Init;
	temp_ADC_Handle.NbrOfCurrentConversionRank 	= 1;
	temp_ADC_Handle.Lock 												= temp_ADC_Lock;
	temp_ADC_Handle.State 											= 0;
	temp_ADC_Handle.ErrorCode 									= HAL_ADC_ERROR_NONE;
	
	// Initialize ADC channel struct
	temp_ADC_Channel.Channel 										= TEMP_ADC_Channel;
	temp_ADC_Channel.Rank 											= 1;															// use to determine the rank in which this channel is sampled
	temp_ADC_Channel.SamplingTime 							= ADC_SAMPLETIME_480CYCLES;				// time for the internal capacitor to charge. longuer means more accurate
	temp_ADC_Channel.Offset											= 0;
	
	// Initialize ADC mode struct
	temp_ADC_Mode.Mode 													= ADC_MODE_INDEPENDENT;														
	temp_ADC_Mode.DMAAccessMode 								= ADC_DMAACCESSMODE_DISABLED;
	temp_ADC_Mode.TwoSamplingDelay 							= ADC_TWOSAMPLINGDELAY_5CYCLES;
	
	TEMP_ADC_CLK_EN;
	if (HAL_ADC_ConfigChannel(&temp_ADC_Handle, &temp_ADC_Channel))
		Error_Handler(ADC_CH_CONFIG_FAIL);
	if (HAL_ADCEx_MultiModeConfigChannel(&temp_ADC_Handle, &temp_ADC_Mode))
		Error_Handler(ADC_MULTIMODE_FAIL);
	
	//GPIO_InitTypeDef GPIO_InitDef; 								
	TEMP_ADC_GPIO_PORT_CLK_EN; 									
	
	GPIO_InitDef.Pin 															= TEMP_ADC_GPIO_PIN; 	
	GPIO_InitDef.Mode 														= GPIO_MODE_ANALOG;   			
	GPIO_InitDef.Pull 														= GPIO_PULLDOWN;
	GPIO_InitDef.Speed 														= GPIO_SPEED_FREQ_MEDIUM;
	
	HAL_GPIO_Init(TEMP_ADC_GPIO_PORT, &GPIO_InitDef);
	
	// STRUCT INITIALIZATION: q, r, x, p, k, f, h
	kalman_struct_init(&vks, 0.02, 50, 0, 50000, 0, 1, 1);
}

// ADC TO FILTERED TEMPERATURE CONVERSION FUNCTION
float temp_adc_conversion(void)
{
	float val 					=	0;
	float filtered_v 		= 0;
	float V25 					= 0.76;	// Voltage at 25 degrees Celcius
	float av_slope			= 2.5/1000;
	
	HAL_ADC_Start(&temp_ADC_Handle);
	if(HAL_ADC_PollForConversion(&temp_ADC_Handle, POLL_TIMEOUT) == HAL_OK)
		val = HAL_ADC_GetValue(&temp_ADC_Handle);
	HAL_ADC_Stop(&temp_ADC_Handle);
	val = (val*3.0f)/4096.0f;
	kalmanfilter(&val, &filtered_v, 1, &vks);
	return ((filtered_v-V25)/av_slope)+25.0f;
}
