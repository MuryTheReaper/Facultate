bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;3/1
    ; a db 1
    ; b dw 2
    ; c dd -3
    ; d dq 4
    
    ;3/2
    ; a db -1
    ; b dw 5
    ; c dd -20
    ; d dq 30
    
    ;Inmultiri si impartiri
    ;3.
    ; a db 1
    ; b db -2
    ; c dd 3 
    ; d db -4
    ; x dq 5
    
; our code starts here
segment code use32 class=code
    start:
        ;3. (c+d)-(a+d)+b
        ; mov EAX, [c]    ;EAX = c = -3 (FFFFFFFDh)
        ; cdq             ;DW to QW => EDX:EAX = c = -3 (FFFFFFFFFFFFFFFDh)
        ; add EAX, [d+0]  ;EAX = EAX + primi 4 bytes al lui d
        ; adc EDX, [d+4]  ;EDX = EDX + ultimi 4 bytes al lui d + CF
                        ; ;EDX:EAX = c+d = -3+4 = 1
        ; mov EBX, EAX    ;Copiem in EBX pe EAX
        ; mov ECX, EDX    ;Copiem in ECX pe EDX
                        ; ;EDX:EAX = ECX:EBX = c+d = 1
        ; mov AL, [a]     ;AL = a = 1
        ; cbw             ;B to W => AX = a = 1
        ; cwde            ;W to DW => EAX = a = 1
        ; cdq             ;DW to QW => EDX:EAX = a = 1
        ; add EAX, [d+0]  ;EAX = EAX + primi 4 bytes al lui d
        ; add EDX, [d+4]  ;EDX = EDX + ultimi 4 bytes al lui d + CF
                        ; ;EDX:EAX = a+d = 5               
        ; sub EBX, EAX    ;EBX = EBX - EAX 
        ; sbb ECX, EDX    ;ECX = ECX - EDX - CF             
                        ; ;ECX:EBX = ECX:EBX - EDX:EAX = (c+d)-(a+d) = 1-5 = -4 (FFFFFFFFFFFFFFFCh)
        ; mov EAX, [b]    ;EAX = b = 2
        ; cwde            ;W to DW => EAX = b = 2
        ; cdq             ;DW to QW => EDX:EAX = b = 2
        ; add EBX, EAX    ;EBX = EBX + EAX
        ; adc ECX, EDX    ;ECX = ECX + EDX + CF
                        ; ;ECX:EBX = (c+d)-(a+d)+b = -4+2 = -2 (FFFFFFFFFFFFFFFEh)
        
        ;3. (c+d)-(a+d)+b FARA SEMN
        ; mov EAX, [c]    ;EAX = c = 4294967293 (FFFFFFFDh)
        ; mov EDX, 0      ;DW to QW => EDX:EAX = c = 4294967293 (FFFFFFFDh)
        ; add EAX, [d+0]  ;EAX = EAX + primi 4 bytes al lui d
        ; adc EDX, [d+4]  ;EDX = EDX + ultimi 4 bytes al lui d + CF
                        ; ;EDX:EAX = c+d = 4294967293+4 = 4294967297 (100000001h)
        ; mov EBX, EAX    ;Copiem in EBX pe EAX
        ; mov ECX, EDX    ;Copiem in ECX pe EDX
                        ; ;EDX:EAX = ECX:EBX = c+d = 4294967297 (100000001h)
        ; mov EAX, 0      ;EAX = 0
        ; mov AL, [a]     ;EAX = a = 1
        ; mov EDX, 0      ;DW to QW => EDX:EAX = a = 1
        ; add EAX, [d+0]  ;EAX = EAX + primi 4 bytes al lui d
        ; add EDX, [d+4]  ;EDX = EDX + ultimi 4 bytes al lui d + CF
                        ; ;EDX:EAX = a+d = 5               
        ; sub EBX, EAX    ;EBX = EBX - EAX 
        ; sbb ECX, EDX    ;ECX = ECX - EDX - CF             
                        ; ;ECX:EBX = ECX:EBX - EDX:EAX = (c+d)-(a+d) = 4294967297-5 = 4294967292 (FFFFFFFCh)
        ; mov EAX, 0      ;EAX = 0
        ; mov AX, [b]     ;EAX = b = 2
        ; mov EDX, 0      ;DW to QW => EDX:EAX = b = 2
        ; add EBX, EAX    ;EBX = EBX + EAX
        ; adc ECX, EDX    ;ECX = ECX + EDX + CF
                        ; ;ECX:EBX = (c+d)-(a+d)+b = 4294967292+2 = 4294967294 (FFFFFFFFFFFFFFFEh)
        
        ;Setul 2 adunari
        ;3.(b+b+d)-(c+a) 
        ; mov AX, [b]       ;AX = b = 5
        ; add AX, [b]       ;AX = AX+b = 5+5 = 10 (Ah)
        ; cwde              ;W to DW => EAX = b+b = 10 (Ah)
        ; cdq               ;DW to QW => EDX:EAX = b+b = 10 (Ah)
        ; add EAX, [d+0]    ;EAX = EAX + primi 4 bytes al lui d
        ; adc EDX, [d+4]    ;EAX = EAX + ultimi 4 bytes al lui d + CF
                          ; ;EDX:EAX = b+b+d = 40 (28h)
        ; mov EBX, EAX      ;Copiem in EBX pe EAX
        ; mov ECX, EDX      ;Copiem in ECX pe EDX
                          ; ;ECX:EBX = EDX:EAX = b+b+d = 40 (28h)
        ; mov AL, [a]       ;AL = a = -1 (FFh)
        ; cbw               ;B to W => AX = a = -1 (FFFFh)
        ; cwde              ;W to DW => EAX = a = -1 (FFFFFFFFh)
        ; add EAX, [c]      ;EAX = EAX+c = a+c = -21 (FFFFFFEBh)
        ; cdq               ;DW to QW => EDX:EAX = a+c = -21 (FFFFFFFFFFFFFFEBh)
        ; sub EBX, EAX      ;EBX = EBX - EAX
        ; sbb ECX, EDX      ;ECX = ECX - EDX - CF
                          ; ;ECX:EBX = (b+b+d)-(c+a) = 61 (3D)
        
        ;Inmultiri si impartiri
        ;3.(8-a*b*100+c)/d+x
        ; mov AL, [a]        ;AL = a = 1
        ; imul byte [b]      ;AX = AL*b = a*b = 1*(-2) = -2 (FFFEh)
        ; mov BX, 100        ;BX = 100 (64h)
        ; imul BX            ;DX:AX = AX*BX = a*b*100 = -2*100 = -200 (FFFFFF38h)
        ; push DX            ;Punem DX in stiva
        ; push AX            ;Punem AX in stiva 
        ; pop EAX            ;EAX = DX:AX  = a*b*100 = -200 (FFFFFF38h)
        ; neg EAX            ;EAX = 0-EAX = -a*b*100 = 200 (C8h)
        ; add EAX, [c]       ;EAX = EAX+c = -a*b*100+c = 203 (CBh)
        ; add EAX, 8         ;EAX = EAX+8 = 8-a*b*100+c = 211 (D3h)
        ; mov EBX, EAX       ;EBX = EAX = 8-a*b*100+c = 211 (D3h)
        ; mov AL, [d]        ;AL = d = -4 (FCh)
        ; cbw                ;B to W => AX = d = -4 (FFFCh)
        ; push EBX           ;Punem EBX in stiva
        ; mov BX, AX         ;BX = AX = d = -4 (FFFCh)
        ; pop AX             ;Incepem sa construim DX:AX
        ; pop DX             ;DX:AX = EBX = 8-a*b*100+c = 211 (D3h)          
        ; idiv BX            ;AX = DX:AX/BX = (8-a*b*100+c)/d = 211/(-4) = -52 (FFCCh)     DX = DX:AX%BX = 3
        ; cwde               ;W to DW => EAX = (8-a*b*100+c)/d = -52 (FFFFFFCCh) 
        ; cdq                ;DW to QW => EDX:EAX = (8-a*b*100+c)/d = -52 (FFFFFFFFFFFFFFCCh)
        ; add EAX, [x+0]     ;EAX = EAX + primi 4 bytes al lui x
        ; adc EDX, [x+4]     ;EDX = EDX + ultimi 4 bytes al lui x + CF
                           ; ;EDX:EAX = (8-a*b*100+c)/d+x = -52+5 = -47 (FFFFFFFFFFFFFFD1h)
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
