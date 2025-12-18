;1. An array with doublewords containing packed data (4 bytes written as a single doubleword) is given. Write an asm program in order to obtain a new array of ;doublewords, where each doubleword will be composed by the rule: the sum of the bytes from an odd position will be written on the word from the odd position and the ;sum of the bytes from an even position will be written on the word from the even position. The bytes are considered to represent signed numbers, thus the extension ;of the sum on a word will be performed according to the signed arithmetic.
;Example:
;for the initial array:
;127F5678h, 0ABCDABCDh, ...
;The following should be obtained:
;006800F7h, 0FF56FF9Ah, ... 
bits 32
global start        
extern exit       
import exit msvcrt.dll    
segment data use32 class=data
s dd 127F5678h, 0ABCDABCDh
l equ ($-s)/4
d resd l
segment code use32 class=code
    start:
        mov esi, s
        mov edi, d 
        mov ecx, 0
        
        parucrugere:
        cmp ecx, l 
        jge stop
  
        lodsd ; eax = s[++index]
        mov ebx, eax ; ebx = eax
        mov dl, al
        movsx edx, byte dl
        and eax, 00FF0000h
        shr eax, 16
        movsx eax, byte al
        add ax, dx ; suma octetilor pari
        movzx eax, ax 
        mov dl, bh 
        movsx edx, byte dl
        and ebx, 0FF000000h
        shr ebx, 24 
        movsx ebx, byte bl
        add bx, dx 
        shl ebx, 16
        or eax, ebx

        stosd
        inc ecx
        jmp parucrugere
        
        stop:
        push    dword 0      
        call    [exit]      
