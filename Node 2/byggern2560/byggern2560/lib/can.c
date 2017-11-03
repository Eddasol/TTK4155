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

	while(mcp2515_Read(MCP_TXB0CTRL) & (1 << MCP_TXREQ));
	mcp2515_Write(MCP_TXB0SIDH, (message.id >> 3));				//Legger identiteten i høy og lav registeret til ID. (til sammen 11bit)
	mcp2515_Write(MCP_TXB0SIDL, (uint8_t)(message.id << 5));
	mcp2515_Write(MCP_TXB0DLC, message.length);					//Setter datalengden i DLC registeret. (4 bit)
	for (int i=0;i<message.length;i++){
		mcp2515_Write(MCP_TXB0D0 + i, message.data[i]);
	}	
	mcp2515_RTS();
}

can_message_t can_read(){
	can_message_t message;
	message.id = ((mcp2515_Read(MCP_RXB0SIDH) << 3) | (mcp2515_Read(MCP_RXB0SIDL) >> 5));
	message.length = mcp2515_Read(MCP_RXB0DLC);
	
	for (int i = 0; i < message.length; i++){
		message.data[i] = mcp2515_Read(MCP_RXB0D0 + i);
	}
	mcp2515_BitModify(MCP_CANINTF, MCP_RX0IF, 0x00);
	
	return message;
}

void can_print(can_message_t message){
	printf("CAN-bus message: (id:%02X, len:%d, data:{", message.id, message.length);
		if(message.length){
			printf("%d", message.data[0]);
		}
		for(uint8_t i = 1; i < message.length; i++){
			printf(", %d", message.data[i]);
		}
	printf("})\n");
}