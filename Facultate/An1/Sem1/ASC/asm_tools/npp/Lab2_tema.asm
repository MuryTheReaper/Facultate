bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit = printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
;Adunare si scadere
    ; 3. a,b,c,d - byte
    ; a db 12
    ; b db 10
    ; c db 27
    ; d db 125

    ; 28. a,b,c,d - byte
    ; a db 11
    ; b db 90
    ; c db 80
    ; d db 10
    
    ; 3. a,b,c,d - word
    ; a dw 321
    ; b dw 256
    ; c dw 500
    ; d dw 400
    
    ; 28. a,b,c,d - word
    ; a dw 300
    ; b dw 400
    ; c dw 500
    ; d dw 600

    
;Inmultire si impartire 
    ; 3. a,b,c - byte, d - word
    ; a db 10
    ; b db 16
    ; c db 11
    ; d dw 300
    
    ; 28. a,b,c - byte, d - word
    ; a db 15
    ; b db 21
    ; c db 12
    ; d dw 270
    
    ; 3. a,b,c,d-byte, e,f,g,h-word
    ; e dw 300
    ; f dw 400
    ; g dw 500
    
    ;28. a,b,c,d-byte, e,f,g,h-word
    ; b db 12
    ; c db 31
    ; d db 19
    ; e dw 300
    ; g dw 400
    ; h dw 500
; our code starts here
segment code use32 class=code
    start:
    ;Adunare si scadere
        ; 3. (c+d)-(a+d)+b
        ; mov AL, [c]  ;AL = c = 27
        ; add AL, [d]  ;AL = c+d = 27+125 = 152
        ; mov BL, [a]  ;BL = a = 12
        ; add BL, [d]  ;BL = a+d = 12+125 = 137
        ; sub AL, BL   ;AL = AL-BL = (c+d)-(a+d) = 152-137 = 15
        ; add AL, [b]  ;AL = AL+b = (c+d)-(a+d)+b = 15+10 = 25
        
        ; 28. a+b-c+d 
        ; mov AL, [a] ;AL = a = 11
        ; add AL, [b] ;AL = a+b = 11+90 = 101
        ; sub AL, [c] ;AL = a+b-c = 101-80 = 21
        ; add AL, [d] ;AL = a+b-c+d = 21+10 = 31
        
        ; 3. (b+b+d)-(c+a)
        ; mov AX, [b] ;AX= b = 256
        ; add AX, [b] ;AX= b+b = 256+256 = 512
        ; add AX, [d] ;AX= b+b+d = 512+400 = 912
        ; mov BX, [c] ;BX= c = 500
        ; add BX, [a] ;BX= c+a = 500+321 = 821
        ; sub AX, BX  ;AX= AX-BX = (b+b+d)-(c+a) = 912-821 = 91
        
        ; 28. (d-c)+(b+b-c-a)+d 
        ; mov AX, [d] ;AX = d = 600
        ; sub AX, [c] ;AX = d-c = 600-500 = 100
        ; mov BX, [b] ;BX = b = 400
        ; add BX, [b] ;BX = b+b = 400+400 = 800
        ; sub BX, [c] ;BX = b+b-c = 800-500 = 300
        ; sub BX, [a] ;BX = b+b-c-a = 300-300 = 0
        ; add AX, BX  ;AX = AX+BX = (d-c)+(b+b-c-a) = 100+0 = 100
        ; add AX, [d] ;AX = (d-c)+(b+b-c-a)+d = 100+600 = 700
        
        
    ;Inmultire si impartire   
        ; 3. [-1+d-2*(b+1)]/a
        ; mov AL, [b]  ;AL = b = 16
        ; inc AL       ;AL = AL+1 = b+1 = 16+1 = 17
        ; mov AH, 2    ;AH = 2
        ; mul AH       ;AX = AL*AH = 17*2 = 34
        ; neg AX       ;AX = 0-AX = -34
        ; add AX, [d]  ;AX = d-2*(b+1) = 300-34 = 266
        ; add AX, -1   ;AX = -1+d-2*(b+1) = -1+266 = 265
        ; div BYTE [a] ;AL = AX/a = 265/10 = 26,  AH = AX%a = 265%10 = 5
        
        ; 28. d+10*a-b*c 
        ; mov BX, [d]  ;BX = d = 270
        ; mov AL, 10   ;AL = 10
        ; mov AH, [a]  ;AH = a = 15
        ; mul AH       ;AX = AL*AH = 15*10 = 150
        ; add BX, AX   ;BX = BX+AX = 150+270 = 420
        ; mov AL, [b]  ;AL = b = 21
        ; mov AH, [c]  ;AH = c = 12
        ; mul AH       ;AX = AL*AH = 21*12 = 252
        ; sub BX, AX   ;BX = BX-AX = 420-252 = 168
        
        ; 3. (e+f)*g 
        ; mov AX, [e]   ;AX = e = 300
        ; add AX, [f]   ;AX = e + f = 300+400 = 700
        ; mul word [g]  ;DX:AX = AX*g = 700*500 = 350000
        ; push DX       ;punem DX in stiva
        ; push AX       ;punem AX in stiva
        ; pop EAX       ;scoatem din stiva DX:AX si punem in EAX
        
        ; 28. (e+g-h)/3+b*c 
        ; mov AX, [e]  ;AX = e = 300
        ; add AX, [g]  ;AX = e+g = 300+400 = 700
        ; sub AX, [h]  ;AX = e+g-h = 700-500 = 200
        ; mov BL, 3    ;BL = 3
        ; div BL       ;AL = AX/BL = 200/3 = 66, AH = AX%BL = 200%3 = 2
        ; mov BL, AL   ;BX = AL = 66
        ; mov BH, 0    ;BH = 0
        ; mov AL, [b]  ;AL = b = 12
        ; mov AH, [c]  ;AH = c = 31
        ; mul AH       ;AX = AL*AH = 12*31 = 372
        ; add BX,AX    ;BX = BX+AX = 66+372 = 438
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
