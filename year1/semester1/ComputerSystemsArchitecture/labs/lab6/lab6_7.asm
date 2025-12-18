;7. A string of doublewords is given. Obtain the list made out of the high bytes of the high words of each doubleword from the given list with the property that ;these bytes are multiple of 3.
;Example:
;Given the string of doublewords:
;s DD 12345678h, 1A2B3C4Dh, FE98DC76h
;obtain the string of bytes:
;d: 12h.
bits 32
global start        
extern exit       
import exit msvcrt.dll    
segment data use32 class=data
s DD 12345678h, 1A2B3C4Dh, 0FE98DC76h
l equ ($-s)
d resb l 
segment code use32 class=code
    start:
        mov esi, s
        mov edi, d 
        mov ecx, 0 
        
        parcurgere:
        cmp ecx, l 
        jge stop
        
        lodsd ; eax = s[++index]
        mov ebp, eax
        mov edx, 0 
        mov ebx, 3 
        div ebx 
        cmp edx, 0 
        jnz nu
        ;este divizibil cu 3 
        mov eax, ebp 
        and eax, 0FF000000h
        shr eax, 24 
        stosb 
        
        nu:
        inc ecx 
        jmp parcurgere
        
        stop:
        push    dword 0      
        call    [exit]      