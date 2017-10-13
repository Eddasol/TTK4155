/*
 * MPC2515.c
 *
 * Created: 11.10.2017 15:49:39
 *  Author: eddas, arild og robin
 */ 

#include "MCP2515.h"
#include "spi.h"
#include <avr/io.h>

void mcp2515_Init(void){
	DDRB |= (1 << PB4);		// Setter ChipSelect for Can Controlleren som output
	SPI_MasterInit();
	printf("Spiworks");
	mcp2515_Reset();
	printf("Mcpinit");
}

uint8_t mcp2515_Read(uint8_t address){
	uint8_t result;
	PORTB &= ~(1 << PB4);	//Lower the CS pin of the can controller
	SPI_MasterTransmit(0b00000011);	//Read
	SPI_MasterTransmit(address);
	result = SPI_SlaveReceive();
	PORTB |= (1 << PB4);	//Put the CS pin high
	return result;
}

void mcp2515_Write(uint8_t address, uint8_t data){
	PORTB &= ~(1 << PB4);	//Lower the CS pin of the can controller
	SPI_MasterTransmit(0b00000010);	//Write
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	PORTB |= (1 << PB4);	//Put the CS pin high
}

void mcp2515_RTS(){
	PORTB &= ~(1 << PB4);	//Lower the CS pin of the can controller
	SPI_MasterTransmit(0b10000001);
	PORTB |= (1 << PB4);	//Put the CS pin high
}

uint8_t mcp2515_ReadStatus(){
	uint8_t status;
	PORTB &= ~(1 << PB4);	//Lower the CS pin of the can controller
	SPI_MasterTransmit(0b10100000);
	status = SPI_SlaveReceive();
	PORTB |= (1 << PB4);	//Put the CS pin high
	return status;
}

void mcp2515_BitModify(uint8_t address, uint8_t maskbyte, uint8_t databyte){
	PORTB &= ~(1 << PB4);	//Lower the CS pin of the can controller
	SPI_MasterTransmit(0b00000101);	//Bit Modify
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(maskbyte);	//A '1' in the mask register will allow a bit in the register to change, while a '0' will not.
	SPI_MasterTransmit(databyte);	//A ‘1’ in the data byte will set the bit and a ‘0’ will clear the bit
	PORTB |= (1 << PB4);	//Put the CS pin high
}

void mcp2515_Reset(){
	PORTB &= ~(1 << PB4);	//Lower the CS pin of the can controller
	SPI_MasterTransmit(0b11000000);
	PORTB |= (1 << PB4);	//Put the CS pin high
}