/*
 * pwmDriver.c
 *
 * Created: 01.11.2017 16:00:38
 *  Author: Arild Stenset
 */ 

 #include "pwm.h"

 void pwmDriver(){						//For høy nok oppløsning bør man benytte 16 bits timer i PWM.
	 DDRH |= (1 << PH6);
	 TCCR2B &= ~(1 << WGM22);
	 TCCR2A |= (1 << WGM21) | (1 << WGM20);
	 TCCR2A |= (1 << COM2B1) | (1 << COM2B0);		//MOtsatt for å kontrollere servo?
	 TCCR2B |= (1 << CS22) | (1 << CS20);
	 TCCR2B &= ~(1 << CS21);
	 OCR2B = 0x14;
 }

 void pwmDriverNy(){
	 // Set pin PH6 as an output pin:
	 DDRH |= (1 << PH6);
	 
	 // Set PWM - mode to 'Fast PWM Mode':
	 TCCR2B |= (1 << WGM22) | (1 << WGM21) | (1 << WGM20);
	 
	 // Set PWM - signal to be active high:
	 TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
	 
	 // Set prescaler to equal 256:
	 TCCR2B |= (1 << CS22) | (1 << CS21);
	 TCCR2B &= ~(1 << CS20);
	 
	 // Set the PWM - frequency:
	 OCR2B = 0x14;
 }

 void pwmDriver3(void){
	 // Set pin PH6 as an output pin:
	 DDRE |= (1 << PE3);
	 
	 // Set PWM - mode to 'Fast PWM Mode':
	 TCCR3A |= (1 << WGM33) | (1 << WGM32) | (1 << WGM31) | (1 << WGM20);
	 
	 // Set PWM - signal to be active high:
	 TCCR3A |= (1 << COM3A1) | (1 << COM3A0);
	 
	 // Set prescaler to equal 256:
	 TCCR2B |= (1 << CS32) | (1 << CS31);
	 TCCR2B &= ~(1 << CS30);
	 
	 ICR3 = 312;
	 
	 // Set the PWM - frequency:
	 OCR2B = 0x14;
 }