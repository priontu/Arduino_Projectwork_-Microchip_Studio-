#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	DDRD = 0xFF;
	PORTD = 0b00000100;
	
	TIMSK1 = 0b00000001;
	TCCR1B = 0b00000100;
	
	
	
	sei();
	
	while(1){
		
	}
}

ISR(TIMER1_OVF_vect) {
	PORTD = (PORTD ^ 0xFF);
}