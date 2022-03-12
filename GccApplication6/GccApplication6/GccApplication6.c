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

int store;

int main(void)
{
	DDRB = 0xFF;
	ADMUX = 0b01000000;
	ADCSRA = 0b11001111;
	DDRC = 0x00;
	
    sei();
    while (1) 
    {

		
		
    }
}

ISR(ADC_vect){
	PORTB = ADCL;
	store = ADCH;
	ADCSRA = 0b11001111;
	
	
}

