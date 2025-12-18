;4. A byte string s is given. Build the byte string d such that every byte d[i] is equal to the count of ones in the corresponding byte s[i] of s.
;Example:
;s: 5, 25, 55, 127
;in binary:
;101, 11001, 110111, 1111111
;d: 2, 3, 5, 7
bits 32
global start        
extern exit       
import exit msvcrt.dll    
segment data use32 class=data
s db 5, 25, 55, 127
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
        
        mov ebx, 0
        mov edx, 0
        lodsb 
        
        parcurgere1:
        cmp edx, 8
        jge finish
        test al, 01h
        jz nu_e_unu
        inc ebx 
        
        nu_e_unu:
        inc edx 
        shr al, 1 
        jmp parcurgere1
        
        finish:
        inc ecx 
        mov al, bl 
        stosb 
        jmp parcurgere
        
        stop:
        push    dword 0      
        call    [exit]      

