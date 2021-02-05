;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop





;registers for this code
	;R0-to display digits
	;R1-keeps track of which bin it is currently on
	;R2-keeps track of how many digits are printed for each bin
	;R3-helps keep track of values after subtracting
	;R4-the data from each bin in the histogram
	;R5-the digit to be displayed 
	;R6-keeps track of bits to determine what digit should be displayed 


;clear the register values
;load the address of the first character in the stringt 
;and put it into R4 
;get the data from that bin and put it into R4
;set R1 to the value of the number of bins so 
;it can keep track of how many bins are displayed
;if that value is zero, all the bins are displayed 
;bin counter keeps track of the bin number so the right 
;number is added to the address to access the right bin in
;the histogram and prints the right letter that is 
;associated with th that historam bin
;constantly keeps track of how many digits are displayed 
;and how many bits are in the digit register and shifts
;the registers based on the values in the register

PRINT_HIST

	AND R0, R0, #0
	AND R1, R1, #0			; bin counter
	AND R2, R2, #0			; digit counter
	AND R3, R3, #0			; rando reg for subtracting
	AND R5, R5, #0
	AND R4, R4, #0			; the data in each bin
	AND R6, R6, #0
	
	LD R4, HIST_ADDR		; put the bin data into register 4
	LDR R4, R4, #0

	LD R1, NUM_BINS			; keeps track of which letter you are printing
	BRz DONE 				; if printed all the letters and bins, then done
	
	
;prints the letter according to the current histogram bin
PRINTLABEL
	AND R0, R0, #0 			;puts new line into R0 and displays it 
	ADD R0, R0, #10
	OUT

	AND R3, R3, #0			;uses NUM_BINS and R6(bin counter)
	NOT R3, R1				;to determine the current bin and then 
	ADD R3, R3, #1			;displays the appropriate letter based
	LD R6, NUM_BINS			;on the value of R6 and the ascii val of A
	ADD R3, R3, R6
	LD R0, HEXFORAT
	ADD R0, R3, R0
	OUT						;displaying out the label

	AND R0, R0, #0			;displaying a space
	LD R0, SPACELAB
	OUT
	
	BRnzp BRINGBACK			;go back to go to the next bin
	
;checks how many digits are printed, and resets the values 
;of R5 and R6 if all 4 digits for one bin are displayed
DIGITSPRINTED
	AND R3, R3, #0
	ADD R3, R2, #-4			; checks the digit counter - 4 to see how many printed digits
	BRz DONEWITHDIGITS  	; if the digits is 4, then it is done with digits
	AND R5, R5, #0			;resets registers
	AND R6, R6, #0

	
;checks if 4 bits are put into R5 the digit register
;also checks to see if R4(register with data from bin)
;has a 1 or 0 in the msb						
BITSNOTFOUR 
	AND R3, R3, #0 
	ADD R3, R6, #-4			; check to see how many bits in R4
	BRz BITCOUNTREADY		; if bitcount R6 is 4, then it is done
	ADD R4, R4, #0		
	BRn PUTBITINDIGIT		;if the msb is 1, then it goes to the label
	ADD R5, R5, R5			;shifts R5 to make sure there is space for another bit
	ADD R5, R5, #0			; put 0 into the 4 bit digit
	ADD R3, R3, #0
	BRn SHIFT				; until the bit counter is 4, it has to go to shift
	BRnzp BITSNOTFOUR		;loops back to beg until done with 4 bits

;shifts the data register and adds one to the bit counter
SHIFT
	ADD R4, R4, R4
	ADD R6, R6, #1
	BRnzp BITSNOTFOUR		;loops back to check if the bit counter is 4
	
;if the msb is 1, it puts the value 1 into the digit(R5)
PUTBITINDIGIT	
	ADD R5, R5, R5			; shifts register to make space
	ADD R5, R5, #1			; adds one to the data reg
	BRnzp SHIFT				; goes to shift the data and inc bit counter

;if 4 bits are done, the digit is checked to see if it is < or > than 9
BITCOUNTREADY
	AND R3, R3, #0			; digit is ready so check if digit is less than 9
	ADD R3, R3, #-9
	ADD R3, R5, R3 			; check if digit count - 9 > 0 
	BRnz OUTO				; if if n or z, then less or eq to 9

;if digit is greater than 9, displays appropriate value
NOTUNDER9					 
	LD R0, HEXFORA
	ADD R0, R0, #-10
	ADD R0, R5, R0
	OUT
	ADD R2, R2, #1			; print a digit, incrememnt digit counter
	BRnzp DIGITSPRINTED		; go back to check how many digits are displayed

;if digit is less than or eq to 9, display digit
OUTO
	AND R0, R0, #0
	LD R3, FORTYEIGHT
	ADD R0, R5, R3		    ; out the digit in hex
	OUT
	ADD R2, R2, #1          ; increment digit counter
	BRnzp DIGITSPRINTED

FORTYEIGHT .FILL #48		; used to display 0

;when each bin is complete, load the address of the first
;character and then use the bin counter (R6) to figure 
;out which bin is next
MOREBINS
	LD R6, HIST_ADDR		;load the addr from label 
	ADD R3, R6, R3
	LDR R4, R3, #0			;add the bin counter to the address to 	
	AND R6, R6, #0 			;find the right bin 
	BRnzp BITSNOTFOUR		;start with checking how many bits are checked

SPACELAB .FILL x0020

;when done with digits in a bin, checks bin counter(R6) to see
;if all the bins are displayed and if not, goes to the print the 
;letter that is the next bin 
DONEWITHDIGITS
	AND R2, R2, #0	
	AND R5, R5, #0			;reset values
	AND R6, R6, #0			;bin counter
	ADD R1, R1, #-1
	BRz DONE
	BRnzp PRINTLABEL

BRINGBACK
	BRnzp MOREBINS

HEXFORA .FILL #65
HEXFORAT .FILL #64

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
;STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
  STR_START	.FILL STRING	; string starting address
  STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."

 ;STR_START	.FILL STRING	; string starting address
 ;STRING		.STRINGZ "AAAAAAAAAAAAA"



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
