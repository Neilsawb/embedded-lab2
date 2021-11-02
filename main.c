#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "timer.h"

#define high 255
#define low 20

int ledCounter = 0;

int main () {
	
	DDRB |= (1<<PB3); // output pin

	fastPWMmode(); // setup fast PWM mode non inverting.
			
	while (1) { // Loop infinitely
		
		PORTB ^= (1<<PB3); // XOR led on PB3
		_delay_ms(1000);
		if (OCR2A == high) {
		OCR2A = low;  // change brightness to low.
		} else {
			OCR2A = high; // change brightness to high.
		} 
	}
}
