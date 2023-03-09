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
        ; s1 db 1, 2, 3, 4
        ; l1 equ $-s1
        ; s2 db 5, 6, 7
        ; l2 equ $-s2
        ; d times l1+l2 db 0
        
        ;5
        ; s db 'a', 'A', 'b', 'B', '2', '%', 'x'
        ; l equ $-s
        ; d times l db 0
        
; our code starts here
segment code use32 class=code
    start:
        ;3.Se dau doua siruri de octeti S1 si S2. Sa se construiasca sirul D prin concatenarea
        ;elementelor din sirul S1 luate de la stanga spre dreapta si a elementelor din sirul S2 luate de la dreapta spre stanga. 
        
        ; mov ECX, l1 ;punem lungimea primului sir in ECX pentru bucla loop
        ; mov ESI, 0
        ; jecxz sfarsit1 ;ne asiguram ca nu intram cu ECX=0 in loop
        ; Repeta1:
            ; mov AL, [s1+ESI] ;Puneam in AL elementele sirului s1 in ordine
            ; mov [d+ESI], AL ;Punem in sirul D elementele sirului s1 in ordine
            ; inc ESI
        ; loop Repeta1
        ; sfarsit1:
        
        ; mov ECX, l2   ;puneam lungimea celui de al doilea sir in ECX pentru bucla loop
        ; mov ESI, 0
        ; jecxz sfarsit2 ;ne asiguram ca nu intram cu ECX=0 in loop
        ; Repeta2:
            ; mov AL, [s2+ECX-1] ;Puneam in AL elementele sirului s2 in ordine inversa 
            ; mov [d+l1+ESI], AL ;Punem in sirul D elementele sirului s2 in ordine inversa
            ; inc ESI
        ; loop Repeta2
        ; sfarsit2:
        
        ;5. Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate literele mici din sirul S.
        
        ; mov ECX, l ;Puneam in ECX lungimea sirului pentru bucla loop
        ; mov ESI, 0
        ; mov EBX, 0 ;Indicele pentru sirul D
        ; jecxz sfarsit
        ; Repeta:
            ; mov AL, [s+ESI] ;Puneam in AL elementele sirului s
            ; cmp AL, 61h ;se poate si cu 'a'
            ; jAE mare_a ;Verificam daca elementul este mai mare sau egal decat caracterul 'a'
            ; jmp next   ;In caz negativ sarim la urmatorul element
            ; mare_a:
                ; cmp AL, 7Ah
                ; jBE mic_z ;Daca elementul este mai mare sau egal decat 'a' verficam daca este mai mic sau egal decat 'z'
                ; jmp next  ;In caz negativ sarim la urmatorul element
                ; mic_z:
                    ; mov [d+EBX], AL ;Daca elementul este intre 'a' si 'z' se punea in sirul D
                    ; inc EBX         ;Indicele lui D creste cu o unitate
            ; next:
            ; inc ESI        
        ; loop Repeta
        ; sfarsit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
