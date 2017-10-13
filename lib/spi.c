/*
 * spi.c
 *
 * Created: 11.10.2017 13:50:29
 *  Author: eddas
 */ 

#include "spi.h"

void SPI_MasterInit(void){
	DDRB |= (1 << PB5) | (1 << PB7);	//Set MOSI and SCK as outputs
	//Set MOSI and SCK output, all others input, SPIE-SPI interrupt enable, SPE-SPI Enable, MSTR-Master/Slave Select
	SPCR |= (1 << SPIE) | (1 << SPE) | (1 << MSTR);
}

void SPI_MasterTransmit(char data){
	
	SPDR = data;	//Start transmission
	
	While(!(SPSR & (1 << SPIF)));	//Waits for a transfer to complete, SPIF is set when a serial transfer is complete. 
	
}

void SPI_SlaveReceive(void){
	while(!(SPSR & (1 << SPIF)));	//Wait for receive completion
	return SPDR;
}