#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>
#include "serial.h"


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
								
	OCR0A = 156;
}


