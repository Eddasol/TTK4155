/*
 * can.c
 *
 * Created: 18.10.2017 14:21:52
 *  Author: eddas
 */ 

#include "can.h"
#include "MCP2515.h"

void can_Init(){
	mcp2515_BitModify(MCP_RXB0CTRL, MCP_FILTER_MASK, 0xFF);		//Filter Off
}

void can_sendMessage(can_message_t message){
	uint8_t idh = (message.id >> 3); 
	uint8_t idl = (message.id << 5);
	while(mcp2515_Read(MCP_TXB0CTRL) & (1 << MCP_TXREQ));
	mcp2515_Write(MCP_TXB0SIDH, (message.id >> 3));				//Legger identiteten i høy og lav registeret til ID. (til sammen 11bit)
	mcp2515_Write(MCP_TXB0SIDL, (uint8_t)(message.id << 5));
	mcp2515_Write(MCP_TXB0DLC, message.length);					//Setter datalengden i DLC registeret. (4 bit)
	for (int i=0;i<message.length;i++){
		mcp2515_Write(MCP_TXB0D0 + i, message.data[i]);
	}	
	mcp2515_RTS();
}

/*
ID - H and L register
Length - some bits in a register
data[] - alot of shit
*/

can_message_t can_read(){
	can_message_t message;
	uint16_t idl;
	uint16_t idh;
	idh = mcp2515_Read(MCP_RXB0SIDH);
	idl = mcp2515_Read(MCP_RXB0SIDL);
	message.id = (idh << 3) | (idl >> 5);
	message.length = mcp2515_Read(MCP_RXB0DLC);
	
	for (int i = 0; i<message.length;i++){
		message.data[i] = mcp2515_Read(MCP_RXB0D0 + i);
	}
	
	return message;
}