/*
 * UART.h
 *
 * Created: 4/25/2024 7:37:56 AM
 *  Author: Nico
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void initUART(int baud_rate, int turbo, int multiprocesador, int sincrono, int paridad, int bit_stop, int cantidad_caracteres, int UBRR0_valor);
void writeUART_car(char caracter);
void writeUART_Text(char* texto);
char receivedChar(void);


#endif /* UART_H_ */