#include <avr/io.h>

#define F_CPU 16000000UL    //Define CPU clock as 16Mhz

#include <util/delay.h>

#include <avr/interrupt.h>

int main(void)

{
	DDRB = 0xFF;	//Why?
	DDRD = 0x00;
	EIMSK = 0b00000001;
	EICRA = 0b00000011;
	sei();
	
	while (1){
		PORTB = 0b00000010;
		_delay_ms(500);
		PORTB = 0b00000000;
		_delay_ms(500);
		
		PORTB = 0b00000100;
		_delay_ms(500);
		PORTB = 0b00000000;
		_delay_ms(500);
		
		PORTB = 0b00001000;
		_delay_ms(500);
		PORTB = 0b00000000;
		_delay_ms(500);
		
		
	}




}


ISR(INT0_vect)
{
	int i;
	for (i = 0; i < 3; i++){
		PORTB = 0xFF;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
	}


}