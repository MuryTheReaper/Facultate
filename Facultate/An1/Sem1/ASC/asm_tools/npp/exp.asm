bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll                    ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 1ah,2bh,3ch,4dh,9fh,6eh,5dh,27h
; our code starts here
segment code use32 class=code
    start:
        ;CD, DF, PF, TF, ZF, SF, AF, IF, OF
        ; mov eax,(2&7)^(23^(~31)); 0000 0010^1111 0111 ->1111 0101 
        ; push eax
        ; push format
        ; call [printf]
        ; add ESP, 4*2
        
        mov al, 10b+10b+10b
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
