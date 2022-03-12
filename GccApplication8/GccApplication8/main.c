/*
Blink 3 leds sequentially, in button interrupt,
gradually increase and then decrease the brightness
of 3 leds altogether. In case of potentiometer exceeding 
such threshold, change direction of leds
blinking sequence.

 * GccApplication6.c
 *
 * Created: 10/5/2021 2:35:00 PM
 * Author : hp
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int threshold, duty;

int main(void)
{
	DDRB = 0xff;
	DDRD = 0x00;
	// External Interrupt (Button)
	EICRA = (1 << ISC00) | (1 < ISC01);
	EIMSK = (1 << INT0);
	sei();
	// FAST PWM
	TCNT1 = 0;
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	TCCR1B = (1 << WGM12) | (1 << CS10);
	TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B = (1 << CS20);
	// Potentiometer
	ADMUX = (1 << REFS0) | (1 << ADLAR);
	ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	while(1){
		// Converting the voltage
		ADCSRA |= (1 << ADSC);
		while(ADCSRA & (1 << ADSC));
		threshold = ADCH;
		if (threshold > 128){
			// Right to Left
			// LED connected to OC1A
			for(duty=0; duty<0xff; duty++)   // 0 to max duty cycle
			{
				OCR1A = duty;     // slowly increase the LED brightness
				_delay_ms(5);
			}
			for(duty=0xff; duty>=0; duty--)   // max to 0 duty cycle
			{
				OCR1A = duty;       // slowly decrease the LED brightness
				_delay_ms(5);
			}
			OCR1A = 0;
			// LED connected to OC1B
			for(duty=0; duty<0xff; duty++)   // 0 to max duty cycle
			{
				OCR1B = duty;     // slowly increase the LED brightness
				_delay_ms(5);
			}
			for(duty=0xff; duty>=0; duty--)   // max to 0 duty cycle
			{
				OCR1B = duty;       // slowly decrease the LED brightness
				_delay_ms(5);
			}
			OCR1B = 0;
			// LED connected to OC2A
			for(duty=0; duty<0xff; duty++)   // 0 to max duty cycle
			{
				OCR2A = duty;     // slowly increase the LED brightness
				_delay_ms(5);
			}
			for(duty=0xff; duty>=0; duty--)   // max to 0 duty cycle
			{
				OCR2A = duty;       // slowly decrease the LED brightness
				_delay_ms(5);
			}
			OCR2A = 0;
		}
		else{
			// Left to Right
			// LED connected to OC2A
			for(duty=0; duty<0xff; duty++)   // 0 to max duty cycle
			{
				OCR2A = duty;     // slowly increase the LED brightness
				_delay_ms(5);
			}
			for(duty=0xff; duty>=0; duty--)   // max to 0 duty cycle
			{
				OCR2A = duty;       // slowly decrease the LED brightness
				_delay_ms(5);
			}
			OCR2A = 0;
			// LED connected to OC1B
			for(duty=0; duty<0xff; duty++)   // 0 to max duty cycle
			{
				OCR1B = duty;     // slowly increase the LED brightness
				_delay_ms(5);
			}
			for(duty=0xff; duty>=0; duty--)   // max to 0 duty cycle
			{
				OCR1B = duty;       // slowly decrease the LED brightness
				_delay_ms(5);
			}
			OCR1B = 0;
			// LED connected to OC1A
			for(duty=0; duty<0xff; duty++)   // 0 to max duty cycle
			{
				OCR1A = duty;     // slowly increase the LED brightness
				_delay_ms(5);
			}
			for(duty=0xff; duty>=0; duty--)   // max to 0 duty cycle
			{
				OCR1A = duty;       // slowly decrease the LED brightness
				_delay_ms(5);
			}
			OCR1A = 0;
		}
	}
}

ISR(INT0_vect) {
	for (int i = 1; i <= 3; i++) {
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

