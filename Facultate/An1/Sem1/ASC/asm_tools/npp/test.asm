bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 12
    b db 10
    c db 27
    d db 125
; our code starts here
segment code use32 class=code
    start:
        
        mov EAX, [c] ;EAX = c = 27
        add EAX, [d] ;EAX = c+d = 27+125 = 152
        mov EBX, [a] ;EBX = a = 12
        add EBX, [d] ;EBX = a+d = 12+125 = 137
        sub EAX, EBX ;EAX = EAX-EBX = (c+d)-(a+d) = 152-137 = 15
        add EAX, [b] ;EAX = EAX+b = (c+d)-(a+d)+b = 15+10 = 25
        

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
