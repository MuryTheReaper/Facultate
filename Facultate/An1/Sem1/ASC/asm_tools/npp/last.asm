bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        x dw -256,256h
        y dw 256|-256, 256h & 256
        z db $-z,y-x
        a db 512>>2, -512<<2
        b dw z-a, !(z-a)
        ;c dd ($-b)+(d-$), $-2*y+3
        d db -128, 128^(~128)
        e times 2 resw 6
; our code starts here
segment code use32 class=code
    start:
        ; mov eax,0
        ; mov edx,0
        ; mov eax, 123456
        ; mov ebx,0
        ; mov ecx,5
        ; .repeta
        ; mov bl,al
        ; shl bl,4
        ; rol bl,4
        ; add dl,bl
        ; shr eax,4
        ; loop .repeta
        movzx ax,[6+ebp*2]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
