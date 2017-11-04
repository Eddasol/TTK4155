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

