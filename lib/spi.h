/*
 * spi.h
 *
 * Created: 11.10.2017 13:50:45
 *  Author: eddas
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#ifndef SPI_H_
#define SPI_H_

void SPI_MasterInit(void);
void SPI_MasterTransmit(char data);
uint8_t SPI_SlaveReceive(void);

#endif /* SPI_H_ */