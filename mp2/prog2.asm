; Partners: smruthi2, manogna3

; This program implements stacks, specifically to calculate a postfix expression that is entered by the user. 
; It is like a stack calculator and uses subroutines to evaluate the expression. It calls on various subroutines 
; such as add, subtract, multiply, divide, power, etc. and prints the result of the expression in hexadecimal. If 
; the expression is invalid, the program will print invalid expression. 


.ORIG x3000
    
; getting input character from the user

GET_INPUT 
 GETC         ; get input character
 OUT          ; display the character

JSR EVALUATE  ; go to evaluate subroutine which determines what the character is




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

; subroutine for printing the final result in hexadecimal

PRINT_HEX 
ST R5, REG5_VALUE       ; saving R5 value
ST R7, REG7_VALUEHEX    ; saving R7 value

; initalizing R0 with 'x' ascii 

INIT                    
LD R0, LETTERX          ; load with 'x' ascii 
OUT                     ; print 'x' to indicate hexadecimal notation


LD R0, LETTER           ; set R0 to ascii character value '['



AND R3, R3, #0          ; clear R3
ADD R3, R3, #4          ; initialize digit counter
AND R4, R4, #0          ; clear R4
ADD R4, R5, #0          ; set R4 to result from R5


; check digitcount and if digit count is 0, go to next histogram value

CHECK_DIGITCOUNT
ADD R3, R3, #0          ; get R3 
BRz RETURN              ; if digitcount is zero, go to RETURN


AND R5, R5, #0          ; clear R5
ADD R5, R5, #4          ; initialize bit counter to 4
AND R6, R6, #0          ; clear R6, the digit

; check bit count and if bit count is 0, go to converting digit to hexadecimal

CHECK_BITCOUNT
ADD R5, R5, #0          
BRz HEXCONVERT          ; if bit count is 0, go to converting to hexadecimal
ADD R6, R6, R6          ; shift digit left

ADD R4, R4, #0          
BRn ADDONE              ; check if value is negative 
ADD R6, R6, #0          ; if value is positive, add 0 to digit


; shift value and decrement bit count
SHIFTHISTVALUE 
ADD R4, R4, R4          ; shift left histogram value
ADD R5, R5, #-1         ; decrement one to bit count
BRnzp CHECK_BITCOUNT    ; go back to checking bit count to see if four bits were reached

; if histogram value is negative, then add one to digit
ADDONE 
ADD R6, R6, #1          ; add one to digit
BRnzp SHIFTHISTVALUE    ; go to shift histogram value



RETURN
LD R7, REG7_VALUEHEX
LD R5, REG5_VALUE
RET              ; if not, go back from subroutine


; convert digit to hexadecimal based on whether it is less than or equal to 9

HEXCONVERT
AND R0, R0, #0        ; clear R0
ADD R0, R6, #-9       ; Add digit with -9 and put in R0
BRnz ADDWITHZERO      ; if this is zero or negative, then go to adding with zero

LD R0, LETTERA        ; set R0 to ascii 'A' value
ADD R6, R6, R0        ; add it with digit 
ADD R6, R6, #-10      ; add to -10 (digit + 'A'-10)
AND R0,R0, #0         ; clear R0
ADD R0, R0, R6        ; set R0 to R6 value 
BRnzp OUTPUT          ; go to output 

; add digit with '0' if digit is less than or equal to 9
ADDWITHZERO
LD R0, ZEROFORHEX         ; set R0 to zero ascii value '0'
ADD R6,R6, R0        ; add digit with zero ascii value and set in R6
AND R0, R0, #0       ; clear R0
ADD R0, R0, R6       ; set R0 to R6 value
BRnzp OUTPUT         ; go to output

; output hexadecimal value 
OUTPUT    
ADD R0, R0, #0       ; get R0 value
OUT                  ; output R0
ADD R3, R3, #-1      ; decrement digit count
BRnzp CHECK_DIGITCOUNT ; go back to check if digit count is zero




LETTER .FILL #91          ; set to '[' ascii value
ZEROFORHEX .FILL #48      ; set to '0' ascii value
LETTERA .FILL #65         ; set to 'A' ascii value
LETTERX .FILL #120        ; set to 'x' ascii value

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output

REG5_VALUE .BLKW #1      ; saving R5 value
REG7_VALUEHEX .BLKW #1   ; saving R7 value


; subroutine to check if character is an operand or operator

EVALUATE
LD R1, EQUAL            ; check if it is the equal ascii '='
NOT R1, R1              
ADD R1, R1, #1         
ADD R1, R1, R0          ; subtract ascii value '=' to see if the entered value is the same.
BRz CHECK_STACKONE      ; check if stack only has one element
LD R1, SPACE            ; load R1 with space ascii 
NOT R1, R1  
ADD R1, R1, #1
ADD R1, R1, R0          ; subtract ascii space value to see if the entered value is the same.
BRz CONTAINS_SPACE      ; go to label if character is space
ADD R1, R1,#0           ; check R1
BRnp CHECK_PLUS         ; if R1 is negative or positive, go to this label.



; go back to getting user input if space ascii is entered

CONTAINS_SPACE
    LD R1, ADDRESS      ; load address to go back in R1
    JMP R1              ; go to this address



; check if character entered is a '+'

CHECK_PLUS
    LD R1, ADDITION     ; load r1 with '+' ascii
    NOT R1, R1
    ADD R1, R1, #1
    ADD R1, R1, R0      ; check if entered input is a '+'
    BRz IS_OPERATORPLUS ; if it is go to label to pop and add values
    ADD R1, R1, #0
    BRnp CHECK_MINUS     ; otherwise, check if input is a '-' ascii




; if input is a '+', then pop two values from stack and add them together.

IS_OPERATORPLUS

    LD R4, STACK_START ; load R4 with stack start 
    LD R5, STACK_TOP   ; load R5 with stack top
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5     ; check if stack is empty, start=top
    BRz INVALID_EXP    ; if it is, go to printing invalid expression message.

    JSR POP            ; pop from stack
    ADD R0, R0, #0     ; clear R0
    AND R3, R3, #0     ; clear R3
    ADD R3, R3, R0     ; intialize R3 with value popped from stack
    
    LD R4, STACK_START ; load R4 with stack start 
    LD R5, STACK_TOP   ; load R5 with stack top
    NOT R4, R4
    ADD R4, R4, #1     
    ADD R4, R4, R5     ; check if stack is empty, start=top
    BRz INVALID_EXP    ; if it is, go to printing invalid expression message.

    JSR POP            ; pop second value from stack
    AND R4, R4, #0     ; clear R4
    ADD R4, R4, R0     ; initalize R4 with value popped from stack
    AND R6, R6, #0     ; clear R6
    ADD R6, R6, #1     ; map 1 to R6 if addition needs to be done
    BRnzp GOTO_RIGHT   ; go to chooosing which operation needs to be done



;checks if the character inputted is a minus

CHECK_MINUS
    LD R1, MINUS        ; load the character into R1
    NOT R1, R1
    ADD R1, R1, #1
    ADD R1, R1, R0         ; subtract value from ascii '-'
    BRz IS_OPERATORMINUS ; if it is, go to label that pops and subtracts
    ADD R1, R1, #0
    BRnp CHECK_MULTIPLY    ; if not, then check if char is *


;pops the values that need to be subtracted
IS_OPERATORMINUS

LD R4, STACK_START        ; load stack start and stack top into regs 
    LD R5, STACK_TOP
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5        ; check if the stack is empty
    BRz INVALID_EXP        ; if so, go to invalid expression



    JSR POP                ; pop one value to be subtracted
    AND R3, R3, #0
    ADD R3, R3, R0

LD R4, STACK_START        ; load stack start and stack top into regs
    LD R5, STACK_TOP    
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5        ; check if the stack is empty
    BRz INVALID_EXP        ; if so, go to invalid expression

    JSR POP                ; pop second value to be subtracted
    AND R4, R4, #0
    ADD R4, R4, R0
    AND R6, R6, #0
    ADD R6, R6, #2         ; map 2 to R6 to do the subtraction

    BRnzp GOTO_RIGHT

;checks if the character inputted is a '*'
CHECK_MULTIPLY
    LD R1, MULTIPLY        ; load the char ascii value into R1
    NOT R1, R1
    ADD R1, R1, #1
    ADD R1, R1, R0        ; subtract the val of char
    BRz IS_OPERATORMULT    ; if char is '*' go to label that pops and multiplies
    ADD R1, R1, #0
    BRnp CHECK_DIVIDE    ; if not, check if the char is '/'
    

;pops the values that need to be multiplied
IS_OPERATORMULT
LD R4, STACK_START        ; check if stack is empty
    LD R5, STACK_TOP    ; start = top
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5
    BRz INVALID_EXP        ; if so, go to invalid exp

    JSR POP                ; pop first value to be multiplied
    AND R3, R3, #0
    ADD R3, R3, R0

    LD R4, STACK_START    ; check if stack is empty
    LD R5, STACK_TOP
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5
    BRz INVALID_EXP        ; if so, go to invalid expression

    JSR POP                ; if not, pop the second value to be multiplied
    AND R4, R4, #0
    ADD R4, R4, R0
    AND R6, R6, #0
    ADD R6, R6, #3         ; map 3 to R6 to multiply popped values
    BRnzp GOTO_RIGHT


;check to see if char inputted is '/'
CHECK_DIVIDE
    LD R1, DIVIDE        ; load the ascii value into R1
    NOT R1, R1
    ADD R1, R1, #1
    ADD R1, R1, R0
    BRz IS_OPERATORDIVIDE ; if it is, go to pop values and divide

    ADD R1, R1, #0        ; otherwise go to check if the operator is a '^'
    BRnp CHECK_POWER

; pops two values to divide
IS_OPERATORDIVIDE
LD R4, STACK_START        ; checks if stack is empty
    LD R5, STACK_TOP
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5
    BRz INVALID_EXP        ; if so, go to invalid exp
        
    JSR POP                ; pop the first value to divide
    AND R3, R3, #0
    ADD R3, R3, R0

LD R4, STACK_START        ; check if stack is empty
    LD R5, STACK_TOP
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5
    BRz INVALID_EXP        ; if so, go to invalid expression

    JSR POP             ; pop from stack
    AND R4, R4, #0
    ADD R4, R4, R0      ; set R4 to value from stack
    AND R6, R6, #0
    ADD R6, R6, #4      ; map 4 to R6 to divide the values
    
    BRnzp GOTO_RIGHT

; check if input is '^'
CHECK_POWER  
    LD R1, POWER
    NOT R1, R1
    ADD R1, R1, #1
    ADD R1, R1, R0       ; subtract '^' ascii from input to see if they are the same
    BRz IS_OPERATORPOWER ; if it is, go to pop values and do exponent
    BRnp IS_OPERAND      ; if not, go to check if the input is an operand


; pop two values from the stack for exponent

IS_OPERATORPOWER  
    LD R4, STACK_START    ; check if stack is empty
    LD R5, STACK_TOP
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5
    BRz INVALID_EXP      ; if stack is empty, go to invalid expression
  
    JSR POP              ; pop value from stack
    AND R3, R3, #0  
    ADD R3, R3, R0       ; set R3 to the value from stack
    LD R4, STACK_START   ; check if stack is empty
    LD R5, STACK_TOP
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R4, R5
    BRz INVALID_EXP      ; if stack is empty, go to invalid expression

    JSR POP              ; pop value from stack
    AND R4, R4, #0
    ADD R4, R4, R0       ; set R4 to the value from stack
    AND R6, R6, #0
    ADD R6, R6, #5       ; map 5 to R6 to do exponent 
    BRnzp GOTO_RIGHT








; check if input is an operand 

IS_OPERAND
    LD R1, ZERO         ; load '0' ascii value
    NOT R1, R1
    ADD R1, R1, #1
    ADD R1, R1, R0      ; subtract from input to see if input is '0'
    ADD R1, R1, #-9     ; Add with offset to see if the input is from 0-9
    BRp INVALID_EXP     ; if not, go to invalid expression
    AND R1, R1, #0      ; clear R1
    LD R1, ZEROHEX      ; load R1 with zero ascii value in hexadecimal
    NOT R1, R1
    ADD R1, R1, #1   
    ADD R0,R1, R0        
    JSR PUSH             ; push value to the stack
    LD R1, STACK_START
    LD R2, STACK_TOP
    NOT R2, R2
    ADD R2, R2, #1
    ADD R1, R1, R2
    LD R7, ADDRESS     
    JMP R7
 





; go to the corresponding label based on value mapped to R6

GOTO_RIGHT             
    ADD R6, R6, #-1
    BRz CALL_PLUS      ; if R6 is 1, go to addition 
    ADD R6, R6, #-1
    BRz CALL_MIN       ; if R6 is 2, go to subtraction 
ADD R6, R6, #-1
    BRz CALL_MULTIPLY  ; if R6 is 3, go to multiplication 
ADD R6, R6, #-1
    BRz CALL_DIVIDE    ; if R6 is 4, go to division
ADD R6, R6, #-1
    BRz CALL_POWER     ; if R6 is 5, go to exponent 
    



; go to subroutine that calculates the addition between the two values

CALL_PLUS
    JSR PLUS          ; go to plus subroutine to add the values
    JSR PUSH          ; push result to stack
    BRnzp GET_INPUT   ; get next input
 

; go to subroutine that calculates the subtraction between the two values


CALL_MIN              
    JSR MIN           ; go to minus subroutine to subtract the values
    JSR PUSH          ; push result to stack
    BRnzp GET_INPUT   ; get next input


; go to subroutine that calculates the multiplication between the values

CALL_MULTIPLY
    JSR MUL           ; go to multiply subroutine
    JSR PUSH          ; push result to stack
    BRnzp GET_INPUT   ; get next input
    
; go to subroutine that calculates the divison between the values

CALL_DIVIDE           
    JSR DIV           ; go to division subroutine
    JSR PUSH          ; push result to stack
    BRnzp GET_INPUT   ; get next input

; go to subroutine that calculates the exponent between the values

CALL_POWER
    JSR EXP           ; go to exponent subroutine
    JSR PUSH          ; push result to stack
    BRnzp GET_INPUT   ; get next input








; check if stack has one element

CHECK_STACKONE

 LD R1, STACK_START    ; load stack start in R1
 LD R5, STACK_TOP      ; load stack top start in R5
 NOT R5, R5  
 ADD R5, R5, #1
 ADD R5, R5, R1        
 ADD R5, R5, #-1       
 BRz LOAD_RESULT       ; if stack has one element, go to loading result
 ADD R5, R5, #0
 BRnp INVALID_EXP      ; if not, go to invalid expression




; popping to final value and calling on a label to display it 
LOAD_RESULT
JSR POP
AND R5, R5, #0
ADD R5, R0, #0
JSR PRINT_HEX            ; call on label to print the final result         


BRnzp DONE


; anytime the stack is empty or an invalid input 
; is entered, display "invalid exp"
INVALID_EXP
    LEA R0, INVALID
    PUTS
    
DONE
HALT


EQUAL .FILL #61        ; '=' is saved
SPACE .FILL #32        ; ' ' is saved
ADDITION  .FILL #43    ; '+' is saved
MINUS .FILL #45        ; '-' is saved
MULTIPLY .FILL #42    ; '*' is saved
DIVIDE   .FILL #47    ; '/' is saved
POWER    .FILL #94    ; '^' is saved
ADDRESS  .FILL x3000;to get input again
ZERO     .FILL #48    ; value of zero is saved
ZEROHEX  .FILL x30    ; hex value of zero saved
INVALID  .STRINGZ " Invalid Expression"
SAVE_REGVALUE .BLKW #1
REG7_VALUE .BLKW #1

STACK_START    .FILL x4000    ;where stack starts and stops
STACK_TOP    .FILL x4000    ;

LD R7, ADDRESS

RET
















;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

;add the two values that were popped
PLUS    
ST R7, REG7_VALUE        ; storing the reg value in memory
ADD R0, R3, R4            ; put result into R0
LD R7, REG7_VALUE        ; load the val from mem into R7
RET                        ; go back to where subrout was called

    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

; subtract the two values that were popped
MIN        
ST R7, REG7_VALUE     ; store reg value in memory
NOT R3, R3
ADD R3, R3, #1        ; negate R3
ADD R0, R3, R4        ; subtract the two values and put in R0
LD R7, REG7_VALUE     ; load value from memory into R7
RET                   ; go back to where the subroutine was called

    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

; multiply the two values that were popped
MUL    
ST R7, REG7_VALUE    ; store reg value in memory

AND R0, R0, #0       ; clear R0

; loop that adds number to itself based on R3 

LOOP
ADD R0, R0, R4        ; add number to R0 in the loop
ADD R3, R3, #-1       ; decrement R3 each time
BRp LOOP              ; go back to loop as long as R3 is positive


LD R7, REG7_VALUE    ; if not load value from memory into R7
RET                  ; go back to where the subroutine was called

    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

; subroutine that divides the two values 
DIV    
ST R7, REG7_VALUE    ; store R7 value into memory
AND R0, R0, #0       ; clear R0
AND R5, R5, #0       ; clear R5
ADD R5, R5, R3       ; add R3 stack value in R5
NOT R5, R5
ADD R5, R5, #1       ; negate R5
ADD R5, R4, R5       ; setting R5 to R4 values
BRn BACK             ; if R5 is negative go to label to go back
   
AND R2, R2, #0       ; clear R2
AND R0, R0, #0       ; clear R0

NOT R3, R3   
ADD R3, R3, #1       ; negate R3

; loop that counts how many times R5 and R4 were subtracted for quotient

LOOP_DIVIDE
ADD R0, R0, #1       ; increment R0 for quotient
ADD R4, R3, R4       ; subtract R3 and R4
BRp LOOP_DIVIDE      ; if positive, go back to loop 





; go back from subroutine

BACK
LD R7, REG7_VALUE   ; load value in R7
RET                 ; go back

    
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

; subroutine that finds the exponent of the two values 

EXP
ST R7, REG7_VALUE   ; store r7 value in memory

AND R2, R2, #0      ; clear R2
AND R6, R6, #0      ; clear R6
ADD R2, R2, R4      ; set R2 to base
ADD R6, R6, R4      ; increment the value


AND R1, R1, #0      ; clear R1
ADD R1, R1, R3      ; R1 initialized to exponent
 

; outer loop to add the base repeatedly until R1 is not positive
OUTER_LOOP          
AND R5, R5, #0      ; clear R5
ADD R5, R5, R4      ; R5 initialized to base
ADD R1, R1, #-1     ; decrement R1 count which is the exponent
BRp INNER_LOOP      ; if R1 is positive go to inner loop
ADD R1, R1, #0      
BRz FINISH          ; check if R1 is 0, and if it is go to finish label


; inner loop to add base repeatedly
INNER_LOOP
ADD R2, R2, R6     ; add base to incremented value
ADD R5, R5, #-1    ; decrement R5, base
AND R0, R0, #0     ; clear R0
ADD R0, R0, #-1    ; decrement R0
ADD R0,R0, R5      ; add R0 with R5 each time in loop until it is not positive

BRp INNER_LOOP     ; go to inner loop, if R0 is positive

AND R6, R6, #0     ; clear R6
ADD R6, R6, R2     ; add base to R6 

ADD R0, R0, #0     ; clear R0
BRz OUTER_LOOP     ; if R0 count is 0, then go to outer loop

; when R1 exponent count is 0, go back

FINISH 
ADD R2, R2, #0    

AND R0, R0, #0      ; clear R0
ADD R0, R0, R2      ; set the result in R0
LD R7, REG7_VALUE   ; load value to R7
RET                 ; go back from subroutine

    







;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH    
    ST R3, PUSH_SaveR3    ;save R3
    ST R4, PUSH_SaveR4    ;save R4
    AND R5, R5, #0        ;
    LD R3, STACK_END    ;
    LD R4, STACk_TOP    ;
    ADD R3, R3, #-1        ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz OVERFLOW        ;stack is full
    STR R0, R4, #0        ;no overflow, store value in the stack
    ADD R4, R4, #-1        ;move top of the stack
    ST R4, STACK_TOP    ;store top of stack pointer
    BRnzp DONE_PUSH        ;
OVERFLOW
    ADD R5, R5, #1        ;
DONE_PUSH
    LD R3, PUSH_SaveR3    ;
    LD R4, PUSH_SaveR4    ;
    RET


PUSH_SaveR3    .BLKW #1    ;
PUSH_SaveR4    .BLKW #1    ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP    
    ST R3, POP_SaveR3    ;save R3
    ST R4, POP_SaveR4    ;save R3
    AND R5, R5, #0        ;clear R5
    LD R3, STACK_START    ;
    LD R4, STACK_TOP    ;
    NOT R3, R3        ;
    ADD R3, R3, #1        ;
    ADD R3, R3, R4        ;
    BRz UNDERFLOW        ;
    ADD R4, R4, #1        ;
    LDR R0, R4, #0        ;
    ST R4, STACK_TOP    ;
    BRnzp DONE_POP        ;
UNDERFLOW
    ADD R5, R5, #1        ;
DONE_POP
    LD R3, POP_SaveR3    ;
    LD R4, POP_SaveR4    ;
    RET


POP_SaveR3    .BLKW #1    ;
POP_SaveR4    .BLKW #1    ;
STACK_END    .FILL x3FF0    ;
;STACK_START    .FILL x4000    ;
;STACK_TOP    .FILL x4000    ;


.END

