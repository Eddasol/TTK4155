/*
 * can.h
 *
 * Created: 18.10.2017 14:22:04
 *  Author: eddas
 */ 


#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>

typedef struct can_message_t can_message_t;
struct can_message_t{
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
	};

void can_Init();
void can_sendMessage(can_message_t message);
void can_read(can_message_t message);

#endif /* CAN_H_ */