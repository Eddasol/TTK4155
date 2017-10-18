/*
 * can.c
 *
 * Created: 18.10.2017 14:21:52
 *  Author: eddas
 */ 

#include "can.h"
#include "MCP2515.h"

void can_sendMessage(can_message_t message){
	uint8_t address = MCP_RTS_TX0;
	
	for (int i=0;i<message.length;i++){
		mcp2515_Write(MCP_RTS_TX0+i, message.data[i]);
	}	
}
ID - H and L register
Length - some bits in a register
data[] - alot of shit

void can_read(can_message_t message){
	uint8_t address = MCP_RTS_TX0;
	for (int i = 0; i<message.length;i++){
		mcp2515_Read(address+i);
	}
}