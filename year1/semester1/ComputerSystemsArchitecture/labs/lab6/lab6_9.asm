bits 32
global start        
extern exit       
import exit msvcrt.dll    
segment data use32 class=data
s dw 1234h, 4567h, 7890h, 0123h
l equ ($-s)/2
d1 resb l 
d2 resb l 
segment code use32 class=code
    start:
        mov esi, s 
        mov edi, d2 
        mov ecx, l
        
        parcurgere;
        lodsw 
        stosb 
        loop parcurgere
        
        mov esi, s 
        mov edi, d1 
        mov ecx, l
        
        parcurgere1:
        lodsw
        shr ax, 8 
        stosb
        loop parcurgere1
        push    dword 0      

        call    [exit]      
