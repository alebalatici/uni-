;5. Two byte strings s1 and s2 are given. Build the byte string d such that, for every byte s2[i] in s2, d[i] contains either the position of byte s2[i] in s1, either ;the value of 0.
;Example:
;pos:1 2 3 4 5
;s1: 7, 33, 55, 19, 46
;s2: 33, 21, 7, 13, 27, 19, 55, 1, 46 
;d: 2,  0, 1, 0, 0, 4, 3, 0, 5
bits 32
global start        
extern exit       
import exit msvcrt.dll    
segment data use32 class=data
s1 db 7, 33, 55, 19, 46
l1 equ ($-s1)
s2 db 33, 21, 7, 13, 27, 19, 55, 1, 46
l2 equ ($-s2)
d resb l2 
segment code use32 class=code
    start:
        mov esi, s2 
        mov edi, d
        mov ecx, 0 
        
        parcurgere:
        cmp ecx, l2 
        jge stop
        lodsb; al = s2[++index]
        mov ebx, 0
        mov edx, 0
        
        parcurgere1:
        cmp ebx, l1 
        jge finish
        cmp al, [s1+ebx]
        jz am_gasit
        inc ebx 
        jmp parcurgere1  
        
        finish:
        mov al, dl  
        stosb
        inc ecx
        jmp parcurgere
        
        am_gasit:
        mov dl, bl 
        inc dl 
        jmp finish
        
        stop:
        push    dword 0      
        call    [exit]      