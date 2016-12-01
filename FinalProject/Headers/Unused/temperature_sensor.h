////////////////////////////////////////////////////////////////////////////////
//	File Name				: temperature_sensor.h
//	Description			: program header
//	Author					: Team 12	
//	Date						: Nov 1st, 2016	
////////////////////////////////////////////////////////////////////////////////

#ifndef _TEMPERATURE_SENSOR_H
#define _TEMPERATURE_SENSOR_H

// DEFINES
#define POLL_TIMEOUT 10000

#define TEMP_ADC											ADC1
#define TEMP_ADC_Channel 							ADC_CHANNEL_TEMPSENSOR
#define TEMP_ADC_CLK_EN 							__HAL_RCC_ADC1_CLK_ENABLE()

#define TEMP_ADC_GPIO_PORT 						GPIOA
#define TEMP_ADC_GPIO_PIN 						GPIO_PIN_5 // Pin A5 is connected to the ADC1 channel 5 input
#define TEMP_ADC_GPIO_PORT_CLK_EN 		__HAL_RCC_GPIOA_CLK_ENABLE(); //Enabling port A clock

// PROTOTYPES
void temp_adc_init(void);
float temp_adc_conversion(void);

#endif /*_TEMPERATURE_SENSOR_H*/
