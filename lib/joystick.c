/*
 * joystick.c
 *
 * Created: 06.11.2017 13:22:10
 *  Author: eddas
 */ 
#include "can.h"
#include "adc.h"
/*
int* calculateJoystickPosition(can_message_t message){
	int calculatedJoystickPositionData[2] = {-1000, -1000};
	// if x position is supposed to have a negative value, set it negative
	if(message.data[2] == 1){
		calculatedJoystickPositionData[0] = message.data[0] - 256;
		}else{
		calculatedJoystickPositionData[0] = message.data[0];
	}
	// if y position is supposed to have a negative value, set it negative
	if(message.data[3] == 1){
		calculatedJoystickPositionData[1] = message.data[1] - 256;
		}else{
		calculatedJoystickPositionData[1] = message.data[1];
	}
	return calculatedJoystickPositionData;
}*/

void joystickDriver() {
	can_message_t* msgJoystickPosition;
	msgJoystickPosition->data[0] = read_x();	// 0b 1110 1101 =			DECIMAL 237
	msgJoystickPosition->data[1] = read_y();	// 0b 1010 0001 =			DECIMAL 161
	//msgJoystickPosition->data[2] = (read_x() < 0) ? 1 : 0;
	//msgJoystickPosition->data[3] = (read_y() < 0) ? 1 : 0;
	msgJoystickPosition->id = 0x00EA;		// 0b 0001 0010 0011 0100 = DECIMAL 4660
	msgJoystickPosition->length = 0x2;		// 0b 0010 =				DECIMAL 2
	
	can_sendMessage(*msgJoystickPosition);
	//can_print(can_read());
	//int* ls = calculateJoystickPosition(*msgJoystickPosition);
	//printf("%i, %i\n", ls[0], ls[1]);
	//printf("%i\n", read_x());
	//_delay_ms(300);
}