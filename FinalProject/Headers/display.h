////////////////////////////////////////////////////////////////////////////////
//	File Name				: display.h	
//	Description			: program header
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _DISPLAY_H
#define _DISPLAY_H

// DEFINES
#define LED_PORT									GPIOD
#define PORT_B_DISP 							GPIOB
#define PORT_E_DISP 							GPIOE

#define GREEN_PIN 								GPIO_PIN_12 // Pin D12 is connected to the onboard green LED
#define ORANGE_PIN 								GPIO_PIN_13	// Pin D13 is connected to the onboard orange LED
#define RED_PIN 									GPIO_PIN_14	// Pin D14 is connected to the onboard red LED
#define BLUE_PIN 									GPIO_PIN_15	// Pin D15 is connected to the onboard blue LED

#define LED_PORT_CLK_EN 					__HAL_RCC_GPIOD_CLK_ENABLE();
#define SEGMENT_CLOCK_B_ENABLE 		__HAL_RCC_GPIOB_CLK_ENABLE();
#define SEGMENT_CLOCK_E_ENABLE 		__HAL_RCC_GPIOE_CLK_ENABLE();

// PROTOTYPES
void rgb_led_init(void);
void gpio_led_init(void);
void segment_display_init(void);
//void segment_segments_init(void);
void display_cycling(void);
void blink_counter(void);
void display(float, int);
void led_number(char, int);
void led_char(char, int);

// DEFINE
#define COUNTERBLINK 100

#endif /*_DISPLAY_H*/
