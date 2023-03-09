bits 32   
extern _printf
global _base_2                      
segment data public data use32

    afis db "Numarul in baza 2 este: %s",10,13,0
	sir times 101 db 0

segment code public code use32

;base_2(nr)
_base_2:
    ;ebp+8 numarul de convertit

    push ebp
    mov ebp, esp   ;crearea cadrului de stiva
    pushad

    mov eax,1           ;in EAX se vor contrui puterile lui 2
    mov ebx,2           ;in EBX se retine 2 ca sa se poata inmulti cu el
    mov ecx,0           ;in ECX se retine cate cifre in baza 2 are numarul de convertit
    nr_cif:
        mul ebx
        inc CL          ;se cauta cea mai mica putere al lui 2 mai mare de numarul de convertit
    cmp eax, [ebp+8]
    jBE nr_cif
    
    sub cl,32
    neg cl
    mov ebx, [ebp+8]
    shl ebx, cl         ;se elimina cifrele de 0 de la inceputul numarului care nu prezinta interes 
                        ;(ex:0011 este egal cu 11)
    sub cl,32
    neg cl
    mov edi, sir
    cld
	bit_by_bit:
        mov al,'0'
        shl ebx, 1      ;se extrage fiecare cifra binara din numar cu operatia shl, se pune in CF 
        adc al, 0       ;si apoi se retine in sirul final de tip string, cifra cu cifra
        stosb
    loop bit_by_bit
    mov al,0
    stosb

    push dword sir
    push dword afis
    call _printf        ;afisez numarul in baza 2 de tip string
    add esp, 4*2

    popad 
    mov esp, ebp
    pop ebp             ;refacerea stivei initiale
	ret 