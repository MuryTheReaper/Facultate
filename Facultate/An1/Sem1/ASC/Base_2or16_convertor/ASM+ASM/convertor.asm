bits 32 
global start        

extern exit, printf          
import exit msvcrt.dll
import printf msvcrt.dll   
extern base_2

segment data use32 class=data public
    mesaj_citire db "Numarul din baza 10 este: %d",10,13,0
    mesaj_afisare2 db "Numarul in baza 2 este: %s",10,13,0
    mesaj_afisare16 db "Numarul in baza 16 este: %X",10,13,0
    sir2 times 101 db 0
    numere dd 64,123,1235,34,12,32
    len equ ($-numere)/4

segment code use32 class=code public
    start:
        mov esi, numere
        mov ecx, len
        cld
        citire:
            lodsd       ;se pune in eax numarul de converiti din sirul 'numere'

            pushad
            push eax
            push dword mesaj_citire
            call [printf]               ;se afiseaza ce numar trebuie convertit
            add ESP, 4*2
            popad
            
            pushad
            push dword sir2
            push eax
            call base_2                 ;se foloseste functia base_2 pentru a pune in 'sir2' numarl convertit in baza 2
            add ESP, 4*2
            popad
            
            pushad
            push dword sir2
            push dword mesaj_afisare2   ;se afiseaza numarul in baza 2
            call [printf]
            add ESP, 4*2
            popad
            
            pushad
            push eax
            push dword mesaj_afisare16  ;se afiseaza numarul in baza 16 cu ajutorul lui printf
            call [printf]
            add ESP, 4*2
            popad
                            
            
        loop citire
        
        ; exit(0)
        push    dword 0      
        call    [exit]       
