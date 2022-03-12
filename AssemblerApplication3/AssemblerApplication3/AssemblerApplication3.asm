.include "m328def.inc" 
.org 0x0000
           RJMP begin; jump to begin  
.org INT0addr
			rjmp ISR1
.org 0x0034
 
 begin:
         LDI    R16,low(RAMEND)
         OUT    SPL,R16
           LDI     R16,high(RAMEND)
         OUT    SPH, R16  
		               
		 LDI    R16,0xFF 
         OUT    DDRB, R16   

		 LDI    R16,0x00 
         OUT    DDRD, R16  

		 LDI R16, 0b00000001
		 OUT EIMSK, R16

		 LDI R16, 0b00000011
		 STS EICRA, R16

		 SEI

turnon: LDI R16, 0xFF
		OUT PORTB, R16
		rjmp turnon

ISR1: LDI R17, 0x00
	  OUT PORTB, R17
	  RCALL Delay
	  RETI

Delay: LDI R17, 0xFc
Delay2: LDI R18, 0xFc
Delay3: LDI R19, 0xFc

loop: DEC R19
	  NOP
	  BRNE loop

	  DEC R18
	  BRNE Delay3

	  DEC R17
	  BRNE Delay2

	  RET

		 
