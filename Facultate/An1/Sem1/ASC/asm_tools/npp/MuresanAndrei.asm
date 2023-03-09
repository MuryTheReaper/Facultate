bits 32 


global start        


extern exit, scanf, fopen, fprintf, fclose, printf              
import exit msvcrt.dll
import scanf msvcrt.dll 
import fopen msvcrt.dll 
import fprintf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll   
                          

segment data use32 class=data
    x dd 0
    m dd 0
    n dd 0
    nr dd 0
    format_citire1 db '%d %d',0
    format_citire2 db '%d',0
    len dd 0
    fisier db 'output.txt',0
    mod_acces db 'a',0
    descriptor dd -1
    format_afisare db '%d',0
    format_afisare2 db ' ',0
    sir dd 0

segment code use32 class=code
    start:
        ;citim de la tastatura
        ;scanf(format_citire1,m,n)
        push dword n
        push dword m
        push dword format_citire1
        call [scanf]
        add esp, 4*3
        
        cld
        mov ecx, [m]
        cmp ecx,0
        je sfarsit
        citire:
            pushad
            push dword x
            push dword format_citire2
            call [scanf]
            add esp, 4*2
            popad
            
            push dword [x]
            mov dword [nr], 0
            verificare:
                pop eax
                mov edx,0
                mov ebx,10
                div ebx
                
                push eax
                mov eax, edx
                mov edx,0
                mov ebx, [n]
                div ebx
                
                cmp edx,0
                jne next_1
                add dword [nr], 1
                next_1:
                pop eax
                push eax
            cmp eax,0
            jne verificare
        pop eax
        cmp dword [nr], 2
        jB next_2
        mov edi, sir
        pop eax
        stosd
        add dword [len], 1
        next_2:
        loop citire
        
        push dword mod_acces
        push dword fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor],eax
        cmp eax, -1
        je sfarsit
        
        mov esi, sir
        cld
        mov ecx, [len]
        afisare:
            pushad
            lodsd
            mov [x],eax
            push dword [x]
            push dword format_afisare
            call [printf]
            add esp,4*2
            popad
            
            pushad
            push dword format_afisare2
            call [printf]
            add esp,4*1
            popad
        loop afisare
        
        push dword [descriptor]
        call [fclose]
        add esp,4
            
            
        
        
        
        
        
                
                
        sfarsit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
