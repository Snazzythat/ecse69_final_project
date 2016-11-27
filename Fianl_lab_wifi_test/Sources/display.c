////////////////////////////////////////////////////////////////////////////////
//	File Name				: display.c
//	Description			: program entry
//	Author					: Team 12
//	Date						: Nov 1st, 2016
////////////////////////////////////////////////////////////////////////////////

// INCLUDES
#include "stm32f4xx_hal.h"
#include "display.h"

// VARIABLE DECLARATION
int display_counter = 0, alarm_counter = 0;

// TIM_LED INITIALIZATION FOR DEBUGGING
/*
** Brief:		Initializes the GPIO periphs used
**					GPGIOs : D12, D13, D14, D15 as output (LED GPIOs)
**
** Params:	None
** Return:	None
*/
void rgb_led_init(void)
{
	__GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin 							= GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStructure.Mode 						= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed 						= GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull 						= GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);
}
 
// INITIALISE LED SEGMENTS
void gpio_led_init(void) 
{
	GPIO_InitTypeDef GPIO_InitDef; 								
	LED_PORT_CLK_EN; 									
	
	GPIO_InitDef.Pin 				= GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8; 	
	GPIO_InitDef.Mode 			= GPIO_MODE_OUTPUT_PP;   			
	GPIO_InitDef.Pull 			= GPIO_NOPULL;
	GPIO_InitDef.Speed 			= GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(LED_PORT, &GPIO_InitDef);
	HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_8, GPIO_PIN_RESET);
}

// INITIALISE 7-SEGMENTS DISPLAYS
void segment_display_init(void)
{
	GPIO_InitTypeDef GPIO_InitDef; 								
	SEGMENT_CLOCK_B_ENABLE;
	
	// INDIVIDUAL DISPLAY MAPPED TO RGB LEDS (PIN 12-15)
	GPIO_InitDef.Pin 				= GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_11; 	
	GPIO_InitDef.Mode 			= GPIO_MODE_OUTPUT_PP;   			
	GPIO_InitDef.Pull 			= GPIO_NOPULL;
	GPIO_InitDef.Speed 			= GPIO_SPEED_FREQ_MEDIUM;
	
	HAL_GPIO_Init(PORT_B_DISP, &GPIO_InitDef);
	HAL_GPIO_WritePin(PORT_B_DISP, GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12|GPIO_PIN_11, GPIO_PIN_RESET);
}

// INITIALIZE THE DISPLAY DIGITS
void segment_segments_init(void)
{
	GPIO_InitTypeDef GPIO_InitDef; 								
	SEGMENT_CLOCK_E_ENABLE;
	
	// INDIVIDUAL DISPLAY MAPPED TO RGB LEDS (PIN 12-15)
	GPIO_InitDef.Pin 				= GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12; 	
	GPIO_InitDef.Mode 			= GPIO_MODE_OUTPUT_PP;   			
	GPIO_InitDef.Pull 			= GPIO_NOPULL;
	GPIO_InitDef.Speed 			= GPIO_SPEED_FREQ_MEDIUM;
	
	HAL_GPIO_Init(PORT_E_DISP, &GPIO_InitDef);
	HAL_GPIO_WritePin(PORT_E_DISP, GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12, GPIO_PIN_RESET);
}

// CYCLING
void display_cycling(void)
{
	if (++display_counter >= 4) // CYCLING BETWEEN THE 4 LED DISPLAYS
	{
		display_counter = 0;
	}
}

// BlINK COUNTER
void blink_counter(void)
{
	if (alarm_counter++ >= COUNTERALARM) // increments every 100 ms, used to count when 0.1 second has passed
	{
		alarm_counter = 0;
	}
}

// DISPLAY SWITCH FUNCTION
void display(float value, int display, int flag)
{
	switch (display)
	{
		// DISPLAY 1
		case 0:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
		
			// CHOOSING WHAT TO DSIPLAY
			if(flag == 0 || flag == 1 || flag == 2)
			{
				if(value >= 0)
				{
					if (value < 100.0f && value >=10.0f){
						led_number((((int)value)%100)/10, 0);
					}else if (value < 10.0f){
						led_number((int)value, 1);
					}else if (value >= 100.0f){
						led_number(((int)value)%1000/100, 0);
					}
				}
			}
			else if(flag == 3)
			{
				if(value >= 0)
				{
					led_char('&', 0); // DISPALY BLANK FOR INPUT
				}
			}
			break;
	
		// DISPLAY 2
		case 1:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
	
			// CHOOSING WHAT TO DSIPLAY
			if(flag == 0 || flag == 1 || flag == 2)
			{
				if(value >= 0)
				{
					if (value < 100.0f && value >=10.0f){
						led_number(((int)value)%100-(((int)value)%100/10)*10, 1);
					}else if (value < 10.0f){
						led_number((int)(value*10)%100-((int)(value*10)%100/10)*10, 0);
					}else if (value >= 100.0f){
						led_number(((int)value)%1000/10-((((int)value)%1000/10)/10)*10,0);
					}
				}
			}
			else if(flag == 3)
			{
				if(value >= 0)
				{
					led_char('&', 0); // DISPALY BLANK FOR INPUT
				}
			}
			break;
	
		// DISPLAY 3
		case 2:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);

			// CHOOSING WHAT TO DSIPLAY
			if(flag == 0 || flag == 1 || flag == 2)
			{
				if(value >= 0)
				{
					if (value < 100.0f && value >=10.0f){
						led_number((int)(value*10)%10, 0);
					}else if (value < 10.0f){
						led_number((int)(value*100)%10, 0);
					}else if (value >= 100.0f){
						led_number(((int)value)%10, 0);
					}
				}
			}
			else if(flag == 3)
			{
				if(value >= 0)
				{
					led_char('&', 0); // DISPALY BLANK FOR INPUT
				}
			}
			break;
	
		// DISPLAY 4
		case 3:
			// INDIVIDUAL DISPLAY TOGGLE
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
			
			// CHOOSING WHAT TO DSIPLAY
			if(flag == 0)
			{
				if(value >= 0)
					led_char('c', 0); // DISPLAY C FOR TEMP
			}
			else if(flag == 1)
			{
				if(value >= 0)
					led_char('|', 0); // DISPLAY - FOR ROLL
			}
			else if(flag == 2)
			{
				if(value >= 0)
					led_char('-', 0); // DISPLAY | FOR PITCH
			}
			else if(flag == 3)
			{
				if(value >= 0)
					led_char('&', 0); // DISPALY BLANK FOR INPUT
			}
			break;
	
		// DISPLAY BLANK
		case -1:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		
		default:
			break;
	}
}

/*
 *Brief:	Toggles the value of the desired pin
 *Params:	None
 *Return:	None
 */

/* 7-SEGMENTS DISPLAY TO STM32F4XX PIN REFERENCE
 *
 *	PIN 14 = PIN D 11			// A
 *	PIN 16 = PIN D 10			// B
 *	PIN 13 = PIN D  9			// C
 *	PIN  3 = PIN D  8			// D
 *	PIN  5 = PIN B 15			// E
 *	PIN 11 = PIN B 14			// F
 *	PIN 15 = PIN B 13 		// G
 *	PIN  7 = PIN B 12			// LOWER DOT
 *	PIN 10 = PIN B 11			// UPPER DOT
*/

// SWITCH STATEMENT FOR CHOSING WHAT NUMBER TO DISPLAY
void led_number(char number, int dot)
{
	switch(number)
	{		
		// DISPLAY NUMBER 0
		case 0:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
			
		// DISPLAY NUMBER 1
		case 1:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
		
		// DISPLAY NUMBER 2
		case 2:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_RESET);				// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 3
		case 3:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		// DISPLAY NUMBER 4
		case 4:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8,	 GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 5
		case 5:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 6
		case 6:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 7
		case 7:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
		  break;
		
		// DISPLAY NUMBER 8
		case 8:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
		  break;
		
		// DISPLAY NUMBER 9
		case 9:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			
		default:
			break;
	}
	
	// DISPLAY DOT
	if(dot==1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);					// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);				// UPPER DOT
	} 
	else if(dot==2)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);				// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);					// UPPER DOT
	}	
	else 
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);				// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);				// UPPER DOT
	}
}

// SWITCH STATEMENT FOR CHOSING WHAT CHARACTER TO DISPLAY
void led_char(char number, int dot)
{
	switch(number)
	{		
		// DISPLAY NOTHING
		case '&':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_RESET);				// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
		
		// DISPLAY 'C'
		case 'c':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_RESET);				// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		// DISPLAY 'P'
		case 'p':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_RESET);				// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		case 'a':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);					// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		case 'b':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		case 'd':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);					// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_SET);					// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_SET);					// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
		
		case '-':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_RESET);				// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);				// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);				// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);					// G
			break;
		
		case '|':
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);				// A
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);				// B
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, 	GPIO_PIN_RESET);				// C
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, 	GPIO_PIN_RESET);				// D
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);					// E
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);					// F
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);				// G
			break;
		
		default:
			break;
	}
	
	// DISPLAY DOT
	if(dot==1)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);					// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);				// UPPER DOT
	} 
	else if(dot==2)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);				// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);					// UPPER DOT
	}	
	else 
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);				// LOWER DOT
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);				// UPPER DOT
	}
}
