/*
 * MPC2515.c
 *
 * Created: 11.10.2017 15:49:39
 *  Author: eddas, arild og robin
 */ 

#include "MCP2515.h"
#include "spi.h"
#include <avr/io.h>
#include <stdio.h>

/*volatile int mcp_interrupt_triggered = 0;

ISR(INT1_vect){
	mcp_interrupt_triggered = 1;
}*/

void mcp2515_Init(void){
	DDRB |= (1 << PB4);											// Setter ChipSelect for Can Controlleren som output
	mcp2515_BitModify(MCP_CANINTE, MCP_RX0IE, MCP_RX0IE);		// Setter det f�rste bitet lik 1
	mcp2515_BitModify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);		// Set mcp in normal mode
}

/*int mcp2515_CheckInterrupt(){
	int temp=mcp_interrupt_triggered;
	mcp_interrupt_triggered=0;
	return temp;
}*/

uint8_t mcp2515_Read(uint8_t address){
	uint8_t result;
	PORTB &= ~(1 << PB4);										// Select chip
	SPI_MasterTransmit(MCP_READ);								// Read
	SPI_MasterTransmit(address);
	result = SPI_MasterTransmit(DONT_CARE);						// Sends DONT_CARE to push the message through
	PORTB |= (1 << PB4);										// Deselect chip
	return result;
}

void mcp2515_Write(uint8_t address, uint8_t data){
	PORTB &= ~(1 << PB4);										// Select chip
	SPI_MasterTransmit(MCP_WRITE);								// Write
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	PORTB |= (1 << PB4);										// Deselect chip
}

void mcp2515_RTS(){
	PORTB &= ~(1 << PB4);										// Select chip
	SPI_MasterTransmit(MCP_RTS_TX0);
	PORTB |= (1 << PB4);										// Deselect chip
}

uint8_t mcp2515_ReadStatus(){
	uint8_t status;
	PORTB &= ~(1 << PB4);										// Select chip
	SPI_MasterTransmit(MCP_READ_STATUS);
	status = SPI_MasterTransmit(0x00);							// 0x00 = send some don't care data, to receive data from the can-controlleren.
	PORTB |= (1 << PB4);										// Deselect chip
	return status;
}

void mcp2515_BitModify(uint8_t address, uint8_t maskbyte, uint8_t databyte){
	PORTB &= ~(1 << PB4);										// Select chip
	SPI_MasterTransmit(MCP_BITMOD);								// Bit Modify
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(maskbyte);								// A '1' in the mask register will allow a bit in the register to change, while a '0' will not.
	SPI_MasterTransmit(databyte);								// A �1� in the data byte will set the bit and a �0� will clear the bit
	PORTB |= (1 << PB4);										// Deselect chip
}

void mcp2515_Reset(){
	PORTB &= ~(1 << PB4);										// Select chip
	SPI_MasterTransmit(MCP_RESET);
	PORTB |= (1 << PB4);										// Deselect chip
}

void mcp2515_PrintMode(){
	uint8_t mode;
	mode = mcp2515_Read(MCP_CANSTAT);
	mode &= 0xE0;
	if(mode == MODE_NORMAL){
		printf("Normal mode\n");
	}
	else if(mode == MODE_LOOPBACK){
		printf("Loopback mode\n");
	}
	else if(mode == MODE_CONFIG){
		printf("Config mode\n");
	}
	else{
		printf("Unknown Mode = %x\n", mode);
	}
}