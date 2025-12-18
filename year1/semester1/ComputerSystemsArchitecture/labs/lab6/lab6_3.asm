;3. An array of doublewords, where each doubleword contains 2 values on a word (unpacked, so each nibble is preceded by a 0) is given. Write an asm program to ;create a new array of bytes which contain those values (packed on a single byte), arranged in an ascending manner in memory, these being considered signed numbers.
;Example:
;for the initial array:
;0702090Ah, 0B0C0304h, 05060108h  
;the following should be obtained:
;72h, 9Ah, 0BCh, 34h, 56h, 18h 
;which arranged in an ascending manner will give:
;9Ah, 0BCh, 18h, 34h, 56h, 72h
bits 32
global start        
extern exit       
import exit msvcrt.dll    
segment data use32 class=data
s dd 0702090Ah, 0B0C0304h, 05060108h
l equ ($-s)/4
d resb l * 2
segment code use32 class=code
    start:
        mov esi, s 
        mov edi, d 
        mov ecx, 0
        
        parcurgere:
        cmp ecx, l 
        jge finish
        
        lodsd ;eax = s[++index]
        mov ebx, eax 
        shr eax, 16; cuvantul high 
        shl ah, 4
        or al, ah ; al = rezultatul
        stosb 
        mov eax, ebx 
        shl ah, 4
        or al, ah ; al = rezultatul
        stosb
        inc ecx 
        jmp parcurgere
        
        finish:
        mov ecx, l * 2
        dec ecx 
        
        parcurgere1:
        mov esi, 0
        mov edx, ecx ; numarul total de comparatii
        
        parcurgere2:
        movsx eax, byte [d+esi]
        movsx ebx, byte [d+esi+1]
        cmp eax, ebx
        jle no_swap
        mov [d+esi+1], al
        mov [d+esi], bl
        
        no_swap:
        inc esi
        dec edx
        jnz parcurgere2
        dec ecx 
        jnz parcurgere1 
        
        stop:
        push    dword 0      
        call    [exit]      