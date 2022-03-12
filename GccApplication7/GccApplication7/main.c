/*
 * GccApplication6.c
 *
 * Created: 10/5/2021 2:35:00 PM
 * Author : hp
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int low;
int high;

int main(void)
{
	DDRB = 0xFF;
	
	ADMUX = 0b01000000;
	ADCSRA = 0b11001111;
	DDRC = 0x00;
	
	TCCR1B = 0b00001001;
	TCCR2B = 0b00000001;
	
	TCCR1A = 0b10100011;
	TCCR2A = 0b10000011;
	
	OCR1A = 0;
	
	sei();
	
	while(1){
	
	}
}

ISR(ADC_vect){
	low = ADCL;
	high = ADCH;
	OCR1A = (low + high*256);
	OCR1B = (low + high*256);
	OCR2A = 256*(low + high*256)/1023;
	ADCSRA = 0b11001111;
}


