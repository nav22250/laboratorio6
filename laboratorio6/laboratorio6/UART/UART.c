/*
 * UART.c
 *
 * Created: 4/25/2024 7:38:38 AM
 *  Author: Nico
 */ 
#include "UART.h"
#include <util/delay.h>

volatile uint8_t bufferTX;
volatile uint8_t valor;

ISR(USART_RX_vect) {
	bufferTX = UDR0;
}

void initUART(int baud_rate, int turbo, int multiprocesador, int sincrono, int paridad, int bit_stop, int cantidad_caracteres, int UBRR0_valor) {
	DDRD &= ~(1 << DDD0);
	DDRD |= (1 << DDD1);
	UCSR0A = 0;

	if (turbo == 1) {
		UCSR0A |= (1 << U2X0);
	}
	if (multiprocesador == 1) {
		UCSR0A |= (1 << MPCM0);
	}

	UCSR0B = 0;
	UCSR0B |= (1 << RXCIE0) | (1 << UDRIE0) | (1 << UDRIE0);
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

	UCSR0C = 0;

	if (sincrono == 1) {
		UCSR0C |= (1 << UMSEL00);
	}
	if (paridad == 1) {
		UCSR0C |= (1 << UPM01);
		} else if (paridad == 2) {
		UCSR0C |= (1 << UPM01) | (1 << UPM00);
	}
	if (bit_stop == 2) {
		UCSR0C |= (1 << USBS0);
	}

	switch (cantidad_caracteres) {
		case 5:
		break;
		case 6:
		UCSR0C |= (1 << UCSZ00);
		break;
		case 7:
		UCSR0C |= (1 << UCSZ01);
		break;
		case 8:
		UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
		break;
		case 9:
		UCSR0C |= (1 << UCSZ02) | (1 << UCSZ01) | (1 << UCSZ00);
		break;
	}

	UBRR0 = UBRR0_valor;
}

void writeUART_car(char caracter) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = caracter;
}

void writeUART_Text(char* texto) {
	uint8_t i;
	for (i = 0; texto[i] != '\0'; i++) {
		while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = texto[i];
	}
}

char receivedChar(void) {
	while (!(UCSR0A & (1 << RXC0)));

	bufferTX = UDR0;

	PORTB = 0;
	PORTC = 0;

	valor = (bufferTX & 0b00111111);

	PORTB |= valor;

	valor = (bufferTX & 0b11000000);
	valor >>= 6;
	PORTC |= valor;
	_delay_ms(1000);
	return UDR0;
}

