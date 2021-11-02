#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "timer.h"

int ledCounter = 0;

int main () {
	
	DDRB |= (1<<PB3); // output pin

	timerZero_init(); // initalise timer 0

	while (1) { // Loop infinitely
		
		if (TCNT0 == 0) { // check if TCNT0 has been reset to zero
			ledCounter++; 
			if (ledCounter == 10) {
				ledCounter = 0; // reset counter for next loop
				PORTB ^= (1<<PB3); // XOR led on PB3
			}
		}
	}
}
