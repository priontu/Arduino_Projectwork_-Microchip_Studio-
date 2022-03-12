#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void){
	DDRD = 0xFF;
	PORTD = 0xff;
	TCNT1 = 0x00;
	
	TIMSK1 = 0b00000010;
	TCCR1B = 0b00001001;
	
	OCR1A = 0xFFFF;
	
	sei();
	
	while(1){
		
	}
}

ISR(TIMER1_COMPA_vect) {
	if (PORTD == 0xFF){
		OCR1A = 3000;
	}
	else{
		OCR1A = 100;
	}
	PORTD ^= 0xff;
}