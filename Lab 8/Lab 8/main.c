/*
 * Lab 8.c
 *
 * Created: 10/18/2021 3:14:36 PM
 * Author : hp
 */ 

#include <avr/io.h>


#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define TRIGPOINT 128

int inc = 0;
int current_led = 1;
int reversed = 0;
int prev_adch = 0;

int main(void){
	cli();
	
	DDRD = 0xFF;
	DDRB = 0xFF;
	DDRC = 0x00;
	//add your codes
	
	//Enable interrupt
	EIMSK = 0b00000001;
	EICRA = 0b00000011;
	
	TCCR1A |= (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1);
	TCCR1B |= (1<<WGM12) | (1<<CS10);
	TCCR2A |= (1<<COM2A1) | (1<<WGM21) | (1<<WGM20);
	TCCR2B |= (1<<CS20);

	// Select ADC0 as ADC input
	ADMUX = 0b00000000;
	// Use AVCC as reference with external capacitor
	ADMUX |= (0<<REFS1)|(1<<REFS0);
	// Configure ADC to be left justified
	ADMUX |= (1<<ADLAR);
	// Enable the ADC and set the prescaler to max value (128)
	ADCSRA = 0b10000111;

	sei();
	
	while(1){
		
		// Start an ADC conversion by setting ADSC bit (bit 6)
		ADCSRA = ADCSRA | (1 << ADSC);
		
		// Wait until the ADSC bit has been cleared
		while(ADCSRA & (1 << ADSC));
		
		if(ADCH <= TRIGPOINT)
		{
			// Original Sequence Order
			
			if(current_led == 1){
				// LED 1
				OCR1A = inc;
				OCR1B = 0;
				OCR2A = 0;
				_delay_ms(20);
				inc += 1;
				
				if(inc >= 255){
					inc = 0;
					OCR1A = 0;
					current_led = 2;
				}
				}else if(current_led == 2){
				// LED 2
				OCR1A = 0;
				OCR1B = inc;
				OCR2A = 0;
				_delay_ms(20);
				inc += 1;
				
				if(inc >= 255){
					inc = 0;
					OCR1B = 0;
					current_led = 3;
				}
				}else if(current_led == 3){
				// LED 3
				OCR1A = 0;
				OCR1B = 0;
				OCR2A = inc;
				_delay_ms(20);
				inc += 1;
				
				if(inc >= 255){
					inc = 0;
					OCR2A = 0;
					current_led = 1;
				}
			}
		}
		else if(ADCH > TRIGPOINT){
			// Reverse Sequence Order
			if(current_led == 1){
				// LED 1
				OCR1A = 0;
				OCR1B = 0;
				OCR2A = inc;
				_delay_ms(20);
				inc += 1;
				
				if(inc >= 255){
					inc = 0;
					OCR2A = 0;
					current_led = 2;
				}
				}else if(current_led == 2){
				// LED 2
				OCR1A = 0;
				OCR1B = inc;
				OCR2A = 0;
				_delay_ms(20);
				inc += 1;
				
				if(inc >= 255){
					inc = 0;
					OCR1B = 0;
					current_led = 3;
				}
				}else if(current_led == 3){
				// LED 3
				OCR1A = inc;
				OCR1B = 0;
				OCR2A = 0;
				_delay_ms(20);
				inc += 1;
				
				if(inc >= 255){
					inc = 0;
					OCR1A = 0;
					current_led = 1;
				}
			}
		}
		
		
		
	}
}

//The interrupt service routine are written inside
ISR(INT0_vect){
	cli();
	
	//your interrupt service routine
	int i=0;
	for(i=0;i<2;i++){
		OCR1A = 0xFF;
		OCR1B = 0xFF;
		OCR2A = 0xFF;
		_delay_ms(200);
		OCR1A = 0;
		OCR1B = 0;
		OCR2A = 0;
		_delay_ms(200);
	}
}

ISR(TIMER1_COMPA_vect){
	PORTB ^= 0xFF;
}




