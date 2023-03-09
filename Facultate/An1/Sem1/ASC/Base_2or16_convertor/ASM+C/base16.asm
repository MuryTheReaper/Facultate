bits 32 
extern _printf
global _base_16                     
segment data public data use32

    afis db "Numarul in baza 16 este: %X",10,13,0

segment code public code use32

_base_16:
    push ebp
    mov ebp, esp            ;crearea cadrului de stiva
    pushad

    mov eax, [ebp+8]
    push eax
    push dword afis         ;se afiseaza cu ajutorul functiei printf direct numarul in baza 16
    call _printf
    add esp, 4*2

    popad 
    mov esp, ebp            ;revenirea la stiva initiala
    pop ebp 
	ret 