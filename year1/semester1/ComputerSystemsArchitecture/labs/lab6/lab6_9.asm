;9. A list of doublewords is given. Starting from the low part of the doubleword, obtain the doubleword made of the high even bytes of the low words of each doubleword ;from the given list. If there are not enough bytes, the remaining bytes of the doubleword will be filled with the byte FFh.
;Example:
;Given the string of doublewords:
;s DD 12345678h, 1A2C3C4Dh, 98FCDD76h, 12783A2Bh
;obtain the doubleword:
;d DD FF3A3C56h
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