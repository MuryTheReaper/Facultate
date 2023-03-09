bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;3
    ;Se dau cuvintele A si B. Sa se obtina dublucuvantul C:
    ;bitii 0-2 ai lui C coincid cu bitii 12-14 ai lui A
    ;bitii 3-8 ai lui C coincid cu bitii 0-5 ai lui B
    ;bitii 9-15 ai lui C coincid cu bitii 3-9 ai lui A
    ;bitii 16-31 ai lui C coincid cu bitii lui A

    ; A dw 0101101001010110b
    ; B dw 1101010111011101b
    ; C resd 1
    ; C =  0101101001010110 1001010 011101 101b => 5A5694EDh
        
    ;10
    ;Sa se inlocuiasca bitii 0-3 ai octetului B cu bitii 8-11 ai cuvantului A. 
    ; A dw 1000011110001011b
    ; B db 11111111b
    ; B =  11110111b => F7h
    
    ;13
    ;Dandu-se 4 octeti, sa se obtina in AX suma numerelor intregi reprezentate de bitii 4-6 ai celor 4 octeti. 
    ; a db 10101101b ; => 010b=2
    ; b db 10110110b ; => 011b=3
    ; c db 11011110b ; => 101b=5
    ; d db 10111101b ; => 011b=3
    
; our code starts here
segment code use32 class=code
    start:
        
        ;3
        ; mov EBX, 0 ;in EBX calculam rezultatul
        
        ; mov AX, [A] 
        ; and AX, 0111000000000000b ;izolam bitii 12-14 al lui A
        ; mov CL, 12
        ; ror AX, CL ;rotim 12 pozitii la dreapta
        ; or  BX, AX ;punem rezultatul in BX
        ; ;BX = 5h
        ; mov AX, [B]
        ; and AX, 0000000000111111b ;izolam bitii 0-5 al lui B
        ; mov CL, 3
        ; rol AX, CL ;rotim 12 pozitii la stanga
        ; or  BX, AX ;punem rezultatul in BX
        ; ;BX = EDh
        ; mov AX, [A]
        ; and AX, 0000001111111000b ;izolam bitii 3-9 al lui A
        ; mov CL, 6
        ; rol AX, CL ;rotim 6 pozitii la stanga
        ; or  BX, AX ;punem rezultatul in BX
        ; ;BX = 94EDh
        ; mov CL, 16
        ; rol EBX,CL ;rotim 16 pozitii la stanga, pentru a avea acces la partea High al lui EBX
        ; mov BX, [A];punem rezultatul in BX
        ; rol EBX,CL ;rotim la loc 16 pozitii la stanga, pentru a aduce partea High la locul potrivit
        ; ;EBX = 5A5694EDh
        ; mov [C],EBX;punem rezultatul in C
        
        ;10
        ; mov AX, [A] 
        ; and AX, 0000111100000000b ;izolam bitii 8-11 al lui A
        ; mov CL, 8
        ; ror AX, CL ;rotim bitii 8 pozitii la dreapta
        ; and byte [B], 11110000b ;izolam bitii 4-7 al lui B
        ; or [B], AL ;introducem bitii lui A in B,  B = F7h
        
        ;13
        ; mov BL, 0 ;punem rezultatul in BL
        
        ; mov AL, [a]
        ; and AL, 01110000b ;izolam bitii 4-6 al lui a
        ; mov CL, 4
        ; ror AL, CL ;rotim 3 pozitii la dreapta
        ; add BL, AL ;BL= BL+2 = 2 
        
        ; mov AL, [b]
        ; and AL, 01110000b ;izolam bitii 4-6 al lui b
        ; mov CL, 4
        ; ror AL, CL ;rotim 3 pozitii la dreapta
        ; add BL, AL ;BL= BL+3 = 5
        
        ; mov AL, [c]
        ; and AL, 01110000b ;izolam bitii 4-6 al lui c
        ; mov CL, 4
        ; ror AL, CL ;rotim 3 pozitii la dreapta
        ; add BL, AL ;BL= BL+5 = 10
        
        ; mov AL, [d]
        ; and AL, 01110000b ;izolam bitii 4-6 al lui d
        ; mov CL, 4
        ; ror AL, CL ;rotim 3 pozitii la dreapta
        ; add BL, AL ;BL= BL+3= 13
        
        
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
