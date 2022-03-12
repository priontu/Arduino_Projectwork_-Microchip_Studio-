#include <avr/io.h>

#define F_CPU 16000000UL    //Define CPU clock as 16Mhz

#include <util/delay.h>

#include <avr/interrupt.h>

You may find the description of the libraries  <avr/io.h> <util/delay.h><avr/interrupt.h> at the online document

http://www.nongnu.org/avr-libc/user-manual/modules.html

You may start your main function as follow?

int main(void)

{


	DDRD = 0xFF;


	//add yourcodes here

}

The interrupt service routine are written as follow:

ISR(XXX_vect)

{

	//add your codes here

}