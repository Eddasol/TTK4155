/*
 * spi.c
 *
 * Created: 11.10.2017 13:50:29
 *  Author: eddas
 */ 

#include "spi.h"
#include <avr/io.h>

void SPI_MasterInit(void){
	DDRB |= (1 << PB5) | (1 << PB7);	//Set MOSI and SCK as outputs
	SPCR |= (1 << SPIE) | (1 << SPE) | (1 << MSTR);	//Set MOSI and SCK output, all others input, SPIE-SPI interrupt enable, SPE-SPI Enable, MSTR-Master/Slave Select
}

void SPI_MasterTransmit(char data){
	
	SPDR = data;	//Start transmission
	
	while(!(SPSR & (1 << SPIF)));	//Waits for a transfer to complete, SPIF is set when a serial transfer is complete. 
	
}

uint8_t SPI_SlaveReceive(void){
	while(!(SPSR & (1 << SPIF)));	//Wait for receive completion
	return SPDR;
}