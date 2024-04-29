//*****************************************************************************
//Universidad del Valle de Guatemala
//IE2023 Programacionde Microcontroladores
//Author : Nicole Navas
//Proyecto: laboratorio 6: UART
//IDescripcion: Codigo conversor UART
//Hardware: ATMega328P
//Created: 4/22/2024 12:22:47 PM
//Actualizado:
//*****************************************************************************
// Encabezado
//*****************************************************************************

#define F_CPU 16000000
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
float const f_cpu= 16000000;
#include "ADC/ADC.h"
#include "UART/UART.h"

volatile uint8_t buffer = 0;
volatile uint8_t valor = 0;
volatile uint8_t op = 0;


void setup() {

	DDRB |= (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB4)|(1<<DDB5);
	DDRC |= (1<<DDC0)|(1<<DDC1);
	
	DDRC &= ~(1 << PC6);
	
}

uint8_t menu(void){
	char mensaje[] = "Ingrese el número correspondiente:\n1. Leer pot\n2. Enviar ASCII\n";
	writeUART_Text(mensaje);
	op = receivedChar();
	if (op >= '1' && op <= '2') {
		return op;
		} else {
		return 0; // Valor de modo inválido
	}
}

int main(void)
{
	initADC();
	initUART(9600, 0, 0, 0, 0, 1, 8, 103);
	setup();
	uint8_t modo=0;
	uint8_t vADC=0;
	char bufferTX[10];
	char ASCII_P[255];
	
	while(1)
	{
		modo=menu();
		
		if (modo=='1'){
			
			vADC=readADC();
			snprintf(bufferTX, sizeof(bufferTX), "%d\n", vADC);
			for (int i = 0; bufferTX[i] != '\0'; i++) {
				writeUART_car(bufferTX[i]);
			}
			writeUART_car('\n');
			} else if (modo=='2'){
			
			snprintf(ASCII_P, sizeof(ASCII_P), "Ingrese el carácter a enviar:\n");
			writeUART_Text(ASCII_P);
			
			buffer=receivedChar();
			valor = (buffer & 0b00111111);
			valor <<=2;
			PORTD |= valor;
			valor = (buffer & 0b11000000);
			valor >>=6;
			PORTB |= valor;
			
			
			} else{
			writeUART_car('\n');
			writeUART_car('\n');
			snprintf(ASCII_P, sizeof(ASCII_P), "No se puede realizar \n");
			writeUART_Text(ASCII_P);
			writeUART_car('\n');
		}

	}
}