#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "timer.h"

volatile int rampValue = 0;
volatile int directionValue = 1;

int main () {
	
	DDRB |= (1<<PB3); // output pin

	fastPWMmode(); // setup fast PWM mode non inverting.

	timerZero_init(); // setup simple CTC timer with 16ms delay.
			
	while (1) { // Loop infinitely
		PORTB ^= (1<<PB3); // XOR led on PB3
		
		if (TCNT0 == 0) {
			rampValue = rampValue + directionValue;
        	simpleRamp(); // checks boundaries if value has reached 0 or 255,if so it flips the sign by * -1.
			OCR2A = rampValue; // uses rampValue as duty cycle for OCR2A. 
		}
	}
}
