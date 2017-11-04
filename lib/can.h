/*
 * can.h
 *
 * Created: 18.10.2017 14:22:04
 *  Author: eddas
 */ 

//Husk � fjern optimalisering. JTAG on Atmel-ICE -> toolchain -> optimalizatoin -> endre flagget fra 01 til 00
#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>

typedef struct can_message_t can_message_t;
struct can_message_t{
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
};

ISR(INT0_vect);
void can_Init();
void can_sendMessage(can_message_t message);
can_message_t can_read();
void can_print(can_message_t message);


#endif /* CAN_H_ */