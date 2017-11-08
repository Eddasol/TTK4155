/*
 * game.c
 *
 * Created: 08.11.2017 11:34:25
 *  Author: Arild Stenset
 */ 
 #include<avr/interrupt.h>

 #include "game.h"

 /*

 void incrementScore(int points){
	 if((score + points) <= maxScore){
		 score += points;
		 }else{
		 score = maxScore;
	 }
 }
 void decrementScore(int points){
	 if((score - points) >= 0){
		 score -= points;
	 }
 }
 void getScore(void){
	 return score;
 }
 void setScore(int points){
	 score = points;
 }

 void initGame(void){
	 score = 0;
	 
 }

 */

 // Interrupt response on pin B0
 void startTimer(void){
	 // Demands an interrupt when an overflow occurs in the Timer/Counter0 occurs:
	 TIMSK0 |= (1 << TOIE0);
	 // Clock Description Bit: clk_(I/O)/No Prescaling -- Comment: Clocking by system clock.
	 TCCR0B |= (1 << CS00);
 }

 void stopTimer(void){
	 // Turns off interrupts triggered by possible overflows in the Timer/Counter0:
	 TIMSK0 &= ~(1 << TOIE0);
	 //CLOCK Description Bit: No clock source (Timer/Counter stopped)
	 TCCR0B &= ~(1 << CS00);
 }

 /*

 ISR(TIMER0_OVF_vect){
	 incrementScore(5);
 }

 */