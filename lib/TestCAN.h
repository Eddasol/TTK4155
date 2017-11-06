/*
 * TestCAN.h
 *
 * Created: 25.10.2017 12:26:15
 *  Author: eddas
 */ 

/*
#ifndef TESTCAN_H_
#define TESTCAN_H_

#include <stdint.h>

typedef struct can_message_t can_message_t;
struct can_message_t{
	uint16_t id; //16bit enough for standard
	uint8_t length; //4bit
	uint8_t data[8]; //8*8bit
};

void can_init(uint8_t operationMode);
void can_messageSend(can_message_t* msg,uint8_t bufferSelect);
uint8_t can_pollInt(void);
can_message_t can_dataReceive(void);
void can_print(can_message_t m);


#endif /* TESTCAN_H_ */*/