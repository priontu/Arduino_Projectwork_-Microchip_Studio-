#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int threshold, counter;


int main(void)
{
    	DDRB = 0xff;
    	DDRD = 0x00;
		

		EICRA = (1 << ISC00) | (1 < ISC01);
		EIMSK = (1 << INT0);
    	sei();
		
    	TCNT1 = 0b00000000;
    	TCCR1B = (1 << WGM12) | (1 << CS10);
    	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    	TCCR2B = (1 << CS20);
    	TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
				
    	ADMUX = (1 << REFS0) | (1 << ADLAR);
    	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
		
		
while(1){
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	threshold = ADCH;
	if (threshold > 128){
		for(counter=0; counter<0xff; counter++) 
		{
			OCR1A = counter;    
			_delay_ms(7);		
		}
		OCR1A = 0;
		for(counter=0; counter<0xff; counter++) 
		{
			OCR1B = counter;  
			_delay_ms(7);
		}
		OCR1B = 0;
		for(counter=0; counter<0xff; counter++) 
		{
			OCR2A = counter;
			_delay_ms(7);
		}
		OCR2A = 0;
	}
	else{
		for(counter=0xff; counter>=0; counter--)  
		{
			OCR1A = counter;      
			_delay_ms(7);
		}
		OCR1A = 0;

		for(counter=0xff; counter>=0; counter--) 
		{
			OCR1B = counter;   
			_delay_ms(7);
		}
		OCR1B = 0;		
		for(counter=0xff; counter>=0; counter--)  
		{
			OCR2A = counter;  
			_delay_ms(7);
		}
		OCR2A = 0;		
	}
}
}

ISR(INT0_vect) {
	for (int i = 1; i <= 1; i++) {
		OCR1A = 0xff;
		OCR1B = 0xff;
		OCR2A = 0xff;
		_delay_ms(500);
		OCR1A = 0x00;
		OCR1B = 0x00;
		OCR2A = 0x00;
		_delay_ms(500);
	}
}