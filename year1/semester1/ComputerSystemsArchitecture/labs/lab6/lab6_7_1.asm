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
s dd 12345678h, 1A2B3C4Dh, 0FE98DC76h
len equ ($ - s)/4
divisor dd 3
d times len resb 1
segment code use32 class=code
start:
    mov esi, s 
    mov edi, d 
    mov ecx, len 
    
    parcurgere:
        cmp ecx, 0 
        je final
        
        lodsd 
        push eax 
        
        mov edx, 0 
        idiv dword [divisor]
        
        pop eax 
        cmp edx, 0 
        jne urm 
        
        shr eax, 24
        stosb  
        
        urm: 
        dec ecx 
        jmp parcurgere
        
    final:
    call [exit]
