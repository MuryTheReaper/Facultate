bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, fopen, fclose, fprintf, scanf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll  
import fprintf msvcrt.dll                         ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll 
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 3.Apeluri de functii sistem
    ; Se dau doua numere naturale a si b (a, b: dword, definite in segmentul de date). 
    ; Sa se calculeze suma lor si sa se afiseze in urmatorul format: "<a> + <b> = <result>"
    ; Exemplu: "1 + 2 = 3"
    ; Valorile vor fi afisate in format decimal (baza 10) cu semn.
    
    ; a dd 78
    ; b dd 123
    ; format_afis db "%d + %d = %d",0
    
    ; 28.Operatii cu fisiere text
    ; Se da un nume de fisier (definit in segmentul de date). 
    ; Sa se creeze un fisier cu numele dat,
    ; apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'.
    ; Sa se scrie in fisier doar cuvintele care contin cel putin o litera mica (lowercase). 
    
    nume_fisier db "Lab8_in.txt",0
    mod_acces db "w",0
    format_citire db "%s",0
    spatiu db ' ',0
    descriptor_fisier dd -1
    x times 101 db 0
    
    
    
; our code starts here
segment code use32 class=code
    start:
        ;3.Apeluri de functii sistem
        ; mov EAX, [a]
        ; add EAX, [b]  ;EAX = a+b = 201
        ; ;printf("%d + %d = %d", a, b, EAX), afisam pe ecran un mesaj
        ; push EAX
        ; push dword [b]
        ; push dword [a]
        ; push dword format_afis
        ; call [printf] 
        ; add ESP, 4*4  ;intoarcem pointarul stivei la momentul initial
        
        ;28.Operatii cu fisiere text
        ; ;EAX=fopen("Lab8_in.txt","w"), deschidem fisierul/se creaza fisierul, in mod scriere
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add ESP, 4*2    ;intoarcem stiva la momentul initial
        cmp EAX, 0   
        je sfarsit      ;daca nu s-a deschid fisierul sarim la sfarsit
        mov [descriptor_fisier], EAX    ;pastram descriptorul fisierului in memorie
        citire:
            pushAD  ;ne asiguram ca nu stricam registrii
            ;scanf("%s", &n), citim de la tastatura cuvinte(siruri de caractere)
            push dword x
            push dword format_citire
            call [scanf]
            add ESP, 4*2    ;intoarcem stiva la momentul initial
            popAD   ;punem registrii inapoi
            cmp byte [x], '$' 
            je inchide     ;daca dam peste caracterul '$' inseamna ca trebuie sa oprim citirea
            
            mov ESI, x
            mov ECX, 100
            mov EBX, 0  ;EBX o sa functioneza ca un OK, EBX=0 daca cuvantul citit nu are niciun caracter litera mica
                        ;EBX=1 daca  cuvantul are cel putin o litera mica
            CLD     ;parcurgem crescator literele cuvantului
            repeta_literamica:
                LODSB   ;punem in AL literele cuvantului
                cmp AL, 0   ;daca AL=0 => am ajuns la sfarsitul cuvantului
                je end_repeta_literamica
                cmp AL, 'a'
                jAE mare_a      ;AL>=a
                    jmp next
                mare_a:
                    cmp AL, 'z' ;AL<=z
                    jBE mic_z
                        jmp next
                    mic_z:
                        mov EBX, 1 ;am gasit litera mica in cuvant => EBX=1
                        jmp end_repeta_literamica
                next:
             loop repeta_literamica
             
             end_repeta_literamica:
                cmp EBX, 1  ;Daca am gasit litera mica in cuvant il punem in fisier
                jne nextt
                    pushAD  ;ne asiguram ca nu stricam registrii
                    ;fprintf(descriptor_fisier, x), scriem in fisier cuvantul care respecta regula
                    push dword x
                    push dword [descriptor_fisier]
                    call [fprintf]
                    add ESP, 4*2    ;intoarcem stiva la momentul initial
                    
                    ;fprintf(descriptor_fisier, spatiu), scriem in fisier caracterul spatiu ca sa despartim cuvntele intre ele
                    push dword spatiu
                    push dword [descriptor_fisier]
                    call [fprintf]
                    add ESP, 4*2
                    popAD   ;punem registrii inapoi
                nextt:
             
        jmp citire
        inchide:
        
        ;fclose(descdescriptor_fisier), inchidem fisierul
        push dword [descriptor_fisier]
        call [fclose]
        add ESP, 4  ;intoarcem stiva la momentul initial
        
        sfarsit:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
