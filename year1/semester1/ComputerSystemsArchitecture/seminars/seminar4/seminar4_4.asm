;4. Se dă un șir de cuvinte S. Să se construiască două șiruri de octeți:
;‒ B1 care are ca elemente partea superioară a cuvintelor din s;
;‒ B2 care are ca elemente partea inferioară a cuvintelor din s.
bits 32
global start        
extern exit       
import exit msvcrt.dll    
segment data use32 class=data
s dw 1234h, 5678h, 9012h, 3456h
; s1 = 12h, 56h, 90h, 34h
; s2 = 34h, 78h, 12h, 56h
l equ ($-s)/2
s1 resb l
s2 resb l
segment code use32 class=code
    start:
        mov ecx, 0
        mov esi, s 
        
        parcurgere:
        lodsw ;ax = esi[index]
        mov [s1+ecx], ah
        mov [s2+ecx], al
        inc ecx 
        cmp ecx, l 
        jnz parcurgere
        
        push    dword 0      
        call    [exit]      
