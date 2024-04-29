/*
 * ADC.c
 *
 * Created: 4/25/2024 8:28:10 AM
 *  Author: Nico
 */ 
#include "ADC.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint16_t vADC = 0;

void initADC(void) {
	ADMUX = 0;
	ADMUX |= (1 << REFS0); // referencia AVCC = 5V

	ADMUX |= (1 << ADLAR);
	ADMUX |= (1 << MUX2) | (1 << MUX1); // Seleccionar canal ADC7

	ADCSRA = 0;
	ADCSRA |= (1 << ADEN); // habilitar ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // habilitación de prescaler

}

uint16_t readADC(void) {
	ADCSRA |= (1 << ADSC); // Iniciar la conversión ADC
	while (ADCSRA & (1 << ADSC)); // Esperar a que la conversión termine
	vADC = ADCH;
	_delay_ms(100);
	return vADC;
}