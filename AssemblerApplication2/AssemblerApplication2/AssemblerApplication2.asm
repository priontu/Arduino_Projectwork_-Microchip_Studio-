.include "m328def.inc" 
.org 0x0000
           RJMP begin; jump to begin  
.org 0x0034 
 begin:    CLI
           LDI    R16,low(RAMEND)
         OUT    SPL,R16
           LDI     R16,high(RAMEND)
         OUT    SPH, R16  
		               
		   LDI    R16,0xFF 
         OUT    DDRD, R16   
		 
blink:	LDI    R16,0xFF 	 
		OUT PORTD, R16
		 RCALL Delay

		 LDI R16, 0x00
		 OUT PORTD, R16
		 RCALL Delay

		 rjmp blink

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
	  

