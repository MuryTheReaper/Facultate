bits 32   
global base_2                      
segment code use32 class=code public

;base_2(nr, sir)
base_2:
    ;esp+0 adresa de return
    ;esp+4 numarul de convertit
    ;esp+8 adresa unde trebuie depus numarul convertit ca string
    mov eax,1           ;in EAX se vor contrui puterile lui 2
    mov ebx,2           ;in EBX se retine 2 ca sa se poata inmulti cu el
    mov ecx,0           ;in ECX se retine cate cifre are numarul de convertit
    nr_cif:
        mul ebx
        inc CL          ;se cauta cea mai mica putere al lui 2 mai mare de numarul de convertit
    cmp eax, [esp+4]
    jBE nr_cif
    
    sub cl,32
    neg cl
    mov ebx, [esp+4]
    shl ebx, cl         ;se elimina cifrele de 0 de la inceputul numarului care nu prezinta interes 
                        ;(ex:0011 este egal cu 11)
    sub cl,32
    neg cl
    mov edi, [esp+8]
    cld
	bit_by_bit:
        mov al,'0'
        shl ebx, 1      ;se extrage fiecare cifra binara din numar cu operatia shl, se pune in CF 
        adc al, 0       ;si apoi se retine in sirul final de tip string, cifra cu cifra
        stosb
    loop bit_by_bit
    mov al,0
    stosb
    ret 
