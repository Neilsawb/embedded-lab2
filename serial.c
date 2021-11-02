#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>
#include "serial.h"

#define high 255
#define low 25


static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void) {
	UBRR0H = (unsigned char)(UBRR >> 8);
	UBRR0L = (unsigned char)(UBRR);
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0 | 1 << RXEN0);
	UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);

	stdout = &uart_stdout;
}

int uart_putchar(char chr, FILE *stream) {
	if (chr == '\n') {
		uart_putchar('\r', NULL);
	}
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = chr;
	return 0;
}

char uart_getchar(void) {
	while (!(UCSR0A & (1 << RXC0)))
		;
	return UDR0;
}

void timerZero_init(void) {

    TCCR0A |= (1<<WGM02);
    TCCR0A &= ~(1 << WGM00);
    TCCR0A &= ~(1 << WGM02);

    //  16MHz (clock cycle) /1024 (prescaler) = 15.625Hz
    // 15.625/((1/10)*1000) = 156,25 (OCR0A = 156)
    TCCR0B |= (1 << CS02)| (0 << CS01) | (1 << CS00); // Prescaler = 1024.

    TCNT0 = 0;

    //OCR0A = 30;

}

void fastPWMmode(void) {
	// Part2 define Fast PWM mode.
	// WGM21=1, WGM20=1 Fast PWM mode 3 with non inverting. (COM2A1)
	
	TCCR2A |= (1<<COM2A1) | (1<<COM2A0) | (1<<WGM21) | (1<<WGM20);

	//  16MHz (clock cycle) /64(prescaler) = 250,000Hz
	// OCR2A = 16000000/(256*64)=16,384 => 976.
	
	TCCR2B |= (1 << CS01) | (1 << CS00); // Prescaler = 64.
									
	TCNT2 = 0;

	OCR2A = low ; // (25) 10% of duty cycle. (255) 100%.
								
	// OCR0A = In Fast PWM mode, the counter is incremented 
	// until the counter value matches the TOP value. The
	// counter is then cleared at the following timer clock cycle.

}


