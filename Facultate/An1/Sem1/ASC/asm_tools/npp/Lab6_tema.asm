bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    ;Se da un sir de 3 dublucuvinte, fiecare dublucuvant continand 2 valori pe cuvant
    ;(despachetate, deci fiecare cifra hexa e precedata de un 0). 
    ;Sa se creeze un sir de octeti care sa contina acele valori (impachetate deci pe un singur octet), 
    ;ordonate crescator in memorie, acestea fiind considerate numere cu semn.
    s dd 0702090Ah, 0B0C0304h, 05060108h
    l equ $-s
    d times l/2 db 0
    ;9Ah=-102, 72h=114, 34h=52, BCh=-68, 18h=24, 56h=86
    ;9Ah, BCh, 18h, 34h, 56h, 72h (sortat crescator)

; our code starts here
segment code use32 class=code
    start:
        ;de la stanga la dreapta(crescator)
        mov ECX, l/2      ;punem in ECX lungimea lui d, pentru loop
        mov ESI, s        ;punem in ESI adresa unde incepe s
        mov EDI, d        ;punem in EDI adresa unde incepe d
        CLD               ;setam DF=0 pentru parcurgere crescatoare
        jecxz sfarsit     ;ne asiguram ca nu intram cu ECX=0 in loop
        repeta:           
            LODSW         ;extragem din s cuvantul de forma 0X0Yh
            push ECX      ;protejam ECX din cauza operatiei de rotire pe biti
            mov CL, 4     ;pregatim rotirea cu 4 pozitii    
            ror AH, CL    ;rotim partea superioara a lui a AH, 0Xh devine X0h
            pop ECX       ;revenim la ECX initial
            add AL, AH    ;combinam cele 2 parti ale cuvantului initia in AL, 0X0Yh(din AX) devine XYh(in AL)
            STOSB         ;stocam octetul obtinut din AL in sirul d
        loop repeta
        
        ;sortare crescatoare de la stanga la dreapta
        mov ESI, 0        ;punem in ESI=0, indice pentru sortare
        repeta_i:
            mov EDI, ESI  
            inc EDI       ;EDI=ESI+1, indice pentru sortare    
            repeta_j:
                mov AL, [d+ESI]
                mov BL, [d+EDI]
                cmp AL,BL         ;se face 'compararea' dintre AL(elementul de pe pozitia ESI) cu BL(elementul de pe pozitia EDI)
                jG swap           ;daca AL>BL atunci se interschimba, daca nu se trece mai departe la urmatorul element
                   jmp next
                swap:
                    mov [d+ESI],BL    ;interschimbarea elementelor
                    mov [d+EDI],AL
                next:
                inc EDI           ;trecem la urmatorul element cu care se compara
            cmp EDI, l/2          ;daca nu mai sunt elemente cu care se compara se trece mai departe
            jB repeta_j
        inc ESI                   ;se trece la urmatorul element de comparat
        cmp ESI, l/2-1            ;daca nu mai este nimic de comparat se termina programul
        jB repeta_i
        sfarsit:
                
                
                
        ; de la dreapta la stanga(descrescator)
        ; mov ECX, l/2      ;punem in ECX lungimea lui d, pentru loop
        ; mov ESI, s+l-2            ;punem in ESI adresa unde se termina s
        ; mov EDI, d+l/2-1          ;punem in EDI adresa unde se termina d
        ; STD               ;setam DF=1 pentru parcurgere descrescatoare
        ; jecxz sfarsit     ;ne asiguram ca nu intram cu ECX=0 in loop
        ; repeta:           
            ; LODSW         ;extragem din s cuvantul de forma 0X0Yh
            ; push ECX      ;protejam ECX din cauza operatiei de rotire pe biti
            ; mov CL, 4     ;pregatim rotirea cu 4 pozitii    
            ; ror AH, CL    ;rotim partea superioara a lui a AH, 0Xh devine X0h
            ; pop ECX       ;revenim la ECX initial
            ; add AL, AH    ;combinam cele 2 parti ale cuvantului initia in AL, 0X0Yh(din AX) devine XYh(in AL)
            ; STOSB         ;stocam octetul obtinut din AL in sirul d
        ; loop repeta
                   
        ;sortare crescatoare de la dreapta la stanga
        ; mov ESI, l/2-1       ;punem in ESI=l/2-1, indice pentru sortare
        ; repeta_i:
            ; mov EDI, ESI  
            ; dec EDI       ;EDI=ESI-1, indice pentru sortare    
            ; repeta_j:
                ; mov AL, [d+ESI]
                ; mov BL, [d+EDI]
                ; cmp AL,BL         ;se face 'compararea' dintre AL(elementul de pe pozitia ESI) cu BL(elementul de pe pozitia EDI)
                ; jL swap           ;daca AL<BL atunci se interschimba, daca nu se trece mai departe la urmatorul element
                   ; jmp next
                ; swap:
                    ; mov [d+ESI],BL    ;interschimbarea elementelor
                    ; mov [d+EDI],AL
                ; next:
                ; dec EDI           ;trecem la urmatorul element cu care se compara
            ; cmp EDI, 0          ;daca nu mai sunt elemente cu care se compara se trece mai departe
            ; jGE repeta_j
        ; dec ESI                   ;se trece la urmatorul element de comparat
        ; cmp ESI, 0            ;daca nu mai este nimic de comparat se termina programul
        ; jG repeta_i
        ; sfarsit:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
