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
	uint8_t id;
	uint8_t length;
	uint8_t data[8];
	};



#endif /* CAN_H_ */