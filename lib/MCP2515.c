/*
 * MPC2515.c
 *
 * Created: 11.10.2017 15:49:39
 *  Author: eddas
 */ 

#include "MCP2515.h"

void mcp2515_init(void){
	
	
}

uint8_t mcp2515_read(uint8_t address){
	uint8_t result;
	PORTB &= ~(1 << PB4);	//Lower the CS pin of the can controller
	SPI_MasterTransmit(0b00000011);
	SPI_MasterTransmit(address);
	result = SPI_SlaveReceive();
	PORTB |= (1 << PB4);	//Put the CS pin high
	return result;
}

void mcp2515_write(){
	
	
}

void mcp2515_RTS(){
	
	
}

void mcp2515_Read