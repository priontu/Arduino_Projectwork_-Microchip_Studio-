#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void){
	DDRB = 0xFF;
	
	TCCR1B = 0b00001001;
	TCCR1A = 0b11000011;
	
	OCR1A = 1015;
	
	while(1){
		_delay_ms(50);
		OCR1A -= 1;
	}
}
