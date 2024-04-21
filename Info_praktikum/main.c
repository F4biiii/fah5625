#include "stm32f4xx.h"
#include "_mcpr_stm32f407.h"
#include <inttypes.h>
#include <stdint.h>
#include "display.h"
#include <stdio.h>

//###############################################
// forward delcaration
//###############################################

void LEDs_InitPorts(void);
void LCD_Output16BitWord(uint16_t data);
void LEDs_Write(uint16_t data);
void u_delay(uint32_t usec);
void LED_blinky(void);
void LEDs_runningLight(void);
void tim7_init(void);
void tim12_init_capture(void);
void tim4_init(void);
void TIM7_IRQHandler(void);
void TIM8_BRK_TIM12_IRQHandler(void);
uint32_t tim12_capture_getticks(void);

//############################################### 
// global variables
//###############################################

static uint32_t ms = 0;							// count milliseconds
static uint32_t s = 0;      				// count seconds

static uint16_t buttonPressed = 0; 	// is user-button pressed?

static uint16_t flag_greenLED = 0;	// greenLED on or off
static uint16_t runningLight_flag = 0; 

static uint16_t tim12_last_capture; 		// remember count of last rising edge (Timer12 measure frequency)
static uint16_t tim12_deltat;						// save the passed time between two rising edges 16bit;
static uint16_t tim12_firstEdge;	

//###############################################
//	functions
//###############################################

void LEDs_InitPorts(void)
{
	RCC->AHB1ENR |= (1 << 4) | (1 << 3) | (1 << 1) | 1; // activate GPIOA, GPIOB, GPOID and GPIOE

	GPIOD->MODER |= (1 << (7 * 2)) | (1 << (11 * 2)) | (1 << (5 * 2)); // set PD11/7/5 to output
	GPIOD->ODR |= (1 << 7) | (1 << 11) | (1 << 5);					  				 // set PD11/7/5 to initial 1

	GPIOD->MODER |= (1 << (12*2)); 		// set PD12 (Green LED) to output
	
	GPIOD->MODER |= (1 << (13*2));		// set PD13 (Display + Orange LED) to output
	GPIOD->ODR |= (1 << 13);					// activate Display / Orange LED
	
	GPIOD->MODER |= (1 << (15 * 2)) | (1 << (14 * 2)) | (1 << (10 * 2)) | (1 << (9 * 2)) | (1 << (8 * 2)) | (1 << (1 * 2)) | 1; // Set LED Ports to output (Peripheral GPIOD)
	GPIOE->MODER |= (1 << (15 * 2)) | (1 << (14 * 2)) | (1 << (13 * 2)) | (1 << (12 * 2)) | (1 << (11 * 2)) | (1 << (10 * 2)) | (1 << (9 * 2)) | (1 << (8 * 2)) | (1 << (7 * 2)); // Set LED Ports to output (Peripheral GPIOE)

	return;
}

void  LCD_Output16BitWord(uint16_t data) // sorts input word to port order
{
	GPIOD->ODR &= 0x3FFF;
	GPIOD->ODR |= (data & 0x0003UL) << 14;

	GPIOD->ODR &= 0xFFFC;
	GPIOD->ODR |= (data & 0x000C) >> 2;

	GPIOD->ODR &= 0xF8FF;
	GPIOD->ODR |= (data & 0xE000) >> 5;

	GPIOE->ODR &= 0x007F;
	GPIOE->ODR |= (data & 0x1FF0UL) << 3;
}

void LEDs_Write(uint16_t data)	// applies port configuration to LEDs
{
	LCD_Output16BitWord(data);		// set status for each LED
	GPIOD->ODR |= 1 << 11;				// PD11 high
	GPIOD->ODR &= ~(1UL << 7);		// PD7 low

	GPIOD->ODR &= ~(1UL << 5);		//	PD5 high-low-high
	u_delay(1);										//
	GPIOD->ODR |= 1 << 5;					//

	GPIOD->ODR |= 1 << 7;					// PD7 high
}

void u_delay(uint32_t usec)			// causes a delay
{
	uint32_t i;
	
	for (i = 0; i < usec; i++) {
		__NOP();
	}
}

void LEDs_runningLight(void)	// causes a running light on the 16 LEDs
{
    static uint16_t i = 0;			// safe the LED position

    if(i < 16) {								// first animation, run single LED
        LEDs_Write(1 << i);  			// move the single 1 over the 16 bits
        i++;
    }
    else if(i < 32) {									// first animation done, keep counting to run single 0
        LEDs_Write(~(1 << (i - 16)));		// move single 0 over the 16 bits, subtract the offset
        i++;
    }
    else {														// both animations are done
        i = 0;													// reset count
    }
}

void tim7_init(void)		// initialize timer (TIM7)
{
	RCC->APB1ENR |= (1 << 5);					// activate Timer 7 Peripheral
	TIM7->PSC = 83;										// set prescaler, every 84th pulse will be counted (168MHz / 2)
	TIM7->ARR = 999;									// counts to 1000
	TIM7->DIER |= 1;									// activate interrupt
	TIM7->CR1 |= 1;										// connect count register to prescaler
	
	NVIC_SetPriority(TIM7_IRQn, 1); 	// set priority 
	NVIC_EnableIRQ(TIM7_IRQn); 				// activate NVIC Interrupt IRQ_Handle

	
}

void tim12_init_capture(void) 	// initialize timer (TIM12)
{
	RCC->APB1ENR |= (1<<6);					// activate Timer 12 Peripheral
	TIM12->PSC = 0;									// set prescaler to 0
	TIM12->ARR = 0xFFFF;						// set auto reload register to maximum
	TIM12->CR1 = 1;									// connect count register to prescaler
	
	TIM12->CCMR1 = 1;								// Select channel 1 (IC1F: 0000), no prescaler (IC1PSC: 00), Selection to input TIy-ICy: (CC1S: 01)
	TIM12->CCER = 1;								// activate enable register TIM12_CCER
	TIM12->CCER &= ~(0x000Au); 			// Set CC1NP and CC1P to 0, get reaction on rising edge 
	TIM12->DIER = 2;								// activate capture interrupt to channel 1
	
	GPIOB->MODER |= (1<< 29);				// set Pin PB14 
	GPIOB->MODER &= ~(1u<<28);  		// to Alternate Function Mode (10)
	GPIOB->AFR[1] = (9 << 24);  		// set PB14 to Alternate Funktion 9, TIM12 Channel 1

	tim12_last_capture = 0;					// reset count of last capture
	tim12_firstEdge = 0;						// reset flag of first edge
	TIM12->SR = 0;									// reset interrupt status register
	
	NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 2);	// set priority
	NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);			// activate NVIC Interrupt IRQ_Handler

}

void tim4_init(void) 					// initialize timer (TIM4)
{
	RCC->APB1ENR |= (1<<2); 				// activate Timer 4 Peripheral
	TIM4->PSC = 8;									// set prescaler to 8 (200Hz base freq)
	TIM4->ARR = 52500;							// set auto reload register to 52.500 (200Hz base freq)
	TIM4->CR1 = 1;									// connect count register to prescaler
	
	TIM4->CCMR1 &= ~(2u << 8);			// channel 2 output mode
	TIM4->CCMR1 |= 5 << 12;					// compare mode 110 (OC2REF active until compare count is reached)
	
	TIM4->CCER &= ~(1u << 4);				// OC2REF active -> active pin-output
	TIM4->CCER &= ~(1u << 7);				
	
	TIM4->CCR2 = 52500 / 2; 				// set brightness to 50% 
	
	GPIOD->MODER |= 1 << 27;				// set Pin PD13 
	GPIOD->MODER &= ~(1u << 26);  	// to Alternate Function Mode (10)
	GPIOD->AFR[1] = 2 << 20;  		// set PD13 to Alternate Funktion 9, TIM12 Channel 1
}


uint32_t tim12_capture_getticks(void)
{
	return (uint32_t) tim12_deltat;
}

//###############################################
// interrupts
//###############################################

void TIM7_IRQHandler(void)
{
	TIM7->SR &= ~(1u<<0);							// reset status bit of interrupt
	ms++;
	
	if(!(ms % 1000)) {				// count seconds every 1000 milliseconds
		s++;
	}
	
	// running light

	if(!(ms % 250)) {												// every 250ms
		runningLight_flag = 1;									// one running light step
	}
	
	// green LED
	
	static uint32_t cnt_greenLED = 0;	
	
	if(cnt_greenLED < 500) {					// count to 500ms (0.5 second)
		cnt_greenLED++;										
	} else {				
		flag_greenLED ^= 1;								// flip flag as 500 is reached
		cnt_greenLED = 0;									// reset count
	}
	
	// display 
	
	static uint32_t cnt_display = 0;	

	if(buttonPressed) {			// is button pressed?
		GPIOD->ODR |= 1 << 13; 						// turn on display
		cnt_display = 0;									// reset count
	} else {													// button is not pressed		
		cnt_display++;									  // count 
	}
	
	if(cnt_display >= 10000) {				// did count reach 10000ms (10s)
		//GPIOD->ODR &= ~(1UL << 13);			// turn off display
		TIM4->CCR2 = 52500 / 2; 					// set brightness to 50% 
		cnt_display = 0;									// reset count
	}
}

void TIM8_BRK_TIM12_IRQHandler(void) 						
{
	uint16_t status = TIM12->SR;
	if( (status & TIM_SR_CC1IF) && tim12_firstEdge) {	// is the interrupt a capture interrupt? is it at least the second flag?
		uint16_t capture = TIM12->CCR1;									// get time of rising edge
		tim12_deltat = capture - tim12_last_capture;		// calculate time between last two rising edges
		tim12_last_capture = capture;										// save time of latest rising edge
	}
	tim12_firstEdge = 1;

}

//###############################################
// main
//###############################################

int main(void)
{ 	
	mcpr_SetSystemCoreClock();
	
	LEDs_InitPorts();											// initialise the required ports
	tim7_init();													// initialize timer 7
	tim12_init_capture();									// initialize timer 12
	tim4_init();													// initialize timer 4
	LCD_Init();														// initialize display
	LCD_ClearDisplay( 0xFE00 );						// clear display
	GPIOD->ODR &= ~(1UL << 13);						// turn off display

	uint32_t init_ms;											// saves content of ms at start of main loop
	
	char str[30];													// array for output string
	char str1[30];												// array for output string
	char str2[30];												// array for output string

	
	while ( 1 ) {													// main loop
		init_ms = ms;													// remember ms at start of main loop
		
		if( (GPIOA->IDR & 1) != 0) {			 		// is button pressed?
			buttonPressed = 1;
		} else {
			buttonPressed = 0;
		}
		
		snprintf(str, 30, "%u seconds", s);							// update time output string 
		LCD_WriteString( 10, 10, 0xFFFF, 0x0000, str);	// output elapsed seconds(display) 
		
		uint32_t ticks = tim12_capture_getticks();			// get time of recent period
			
		snprintf(str1, 30, "%d ticks", ticks);					// output recend period
		LCD_WriteString(10, 50, 0xFFFF, 0x0000, str1);	//
		
		uint32_t frequency;		
		frequency = 84000000/ticks;											// calculate frequency in Hertz
		snprintf(str2, 30, "%d Hz", frequency);					// output calculated frequency
		LCD_WriteString(10, 70, 0xFFFF, 0x0000, str2 );	//
		
		tim12_init_capture();														// reinitialize all
		
		if(buttonPressed) {			 						// is button pressed?		
			TIM4->CCR2 = 52500; 								// set brightness to 100% 
			if(flag_greenLED) {									// shall green LED be on or off? (flag switches every 500ms)
				GPIOD->ODR |= 1 << 12;							// turn on green LED
			} else {
				GPIOD->ODR &= ~(1UL << 12);					// turn off green LED
			}
		} else {															// button is not pressed
				GPIOD->ODR &= ~(1UL << 12);					// turn off green LED		
		}
		
		if(runningLight_flag) {								// every 250ms
			LEDs_runningLight();									// do a running light step
			runningLight_flag = 0;								// reset flag
		}
		
		if((!buttonPressed) && (TIM4->CCR2 > (52500/2))) {	// button is not pressed and display is brighter than 50%
			TIM4->CCR2 -= (52500 / 100);													// reduce brightness by 1%
		} else if(TIM4->CCR2 < (52500/2)) {							
			TIM4->CCR2 = 52500 / 2;			
		}
		
		while(ms < (init_ms + 50)) {					// until 50ms have passed
			__NOP();															// do nothing
		}
	}
}
