bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;3.Operatii cu fisiere text
    ;Se da un fisier text. 
    ;Sa se citeasca continutul fisierului, sa se contorizeze numarul de cifre pare si sa se afiseze aceasta valoare.
    ;Numele fisierului text este definit in segmentul de date. 
    
    nume_fisier db "Lab8_in_bonus.txt",0
    ;1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1 
    mod_acces db "r",0
    descriptor_fisier dd -1
    nr_car_citite dd 0
    len equ 100
    date_fisier times (len+1) db 0
    format db "Numarul de cifre pare din fisier este: %d",10,13,0
    nr dd 0

; our code starts here
segment code use32 class=code
    start:
    
        ;3.Operatii cu fisiere text
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add ESP, 4*2
        cmp EAX, 0
        je sfarsit
        mov [descriptor_fisier], EAX
        
        citire:
            push dword  [descriptor_fisier]
            push dword len
            push dword 1
            push dword date_fisier
            call [fread]
            add ESP, 4*4
            
            cmp EAX, 0
            je inchidere
            mov [nr_car_citite], EAX

            mov EAX, [nr_car_citite]
            push EAX
            pop AX
            pop DX
            mov BX, 2
            div BX
            mov ECX, 0
            mov CX, AX
            mov ESI, date_fisier
            CLD
            repeta:
                LODSW
                sub AL,'0'
                mov AH,0
                mov BL,2
                div BL
                cmp AH,0
                je par
                    jmp next
                par:
                    add dword [nr],1
                next:
            loop repeta
                
            
            jmp citire
        
        
        inchidere:
            push dword [descriptor_fisier]
            call [fclose]
            add ESP, 4*1
            
            push dword [nr]
            push dword format
            call [printf]
            
        sfarsit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
