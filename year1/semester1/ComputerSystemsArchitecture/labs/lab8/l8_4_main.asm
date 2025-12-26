; https://github.com/alebalatici/uni-
; l8_4_main.asm + l8_4_convert16.asm + l8_4_convert2.asm
bits 32 
global start        
extern exit              
extern printf 
import exit msvcrt.dll    
import printf msvcrt.dll 
%include "l8_4_convert16.asm"
%include "l8_4_convert2.asm"
segment data use32 class=data
s dd 12496, 45443, 4534243, 53784, 3546465, 5364
l equ ($-s)/4
s1 dd 2, 6, 100, 64, 128, 4
x dd 0 
aux times 50 db 0
base16 times 10 db 0 
base2 times 50 db 0
format16 db "x(16) = %s", 10, 0  
format2 db "x(2) = %s", 10, 0  
frm db "x = %d", 10, 0 
segment code use32 class=code
    start:
        mov ecx, 0
        parcurgere:
        cmp ecx, l 
        jge stop
        push ecx
        
        mov eax, [s + ecx*4]
        mov [x], eax 
        
        push dword eax 
        push dword frm
        call [printf]
        add esp, 8
        
            ;clear aux 
            mov ecx, 50 
            mov edi, aux 
            xor eax, eax 
            rep stosb 
    
            mov eax, [x]
            call convertire16
        
            afisare16:
            push dword base16 
            push dword format16 
            call [printf]
            add esp, 8 
        
            ;clear aux 
            mov ecx, 50 
            mov edi, aux 
            xor eax, eax 
            rep stosb 
       
            mov eax, [x]
            call convertire2
        
            afisare2:
            push dword base2 
            push dword format2 
            call [printf]
            add esp, 8  
        
        pop ecx 
        inc ecx
        jmp parcurgere
    
    stop:
        push    dword 0
        call    [exit]     
