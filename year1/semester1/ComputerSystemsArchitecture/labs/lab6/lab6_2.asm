;2. An array of words is given. Write an asm program in order to obtain an array of doublewords, where each doubleword will contain each nibble unpacked on a byte ;(each nibble will be preceded by a 0 digit), arranged in an ascending order within the doubleword.
;Example:
;for the initial array:
;1432h, 8675h, 0ADBCh
;The following should be obtained:
;01020304h, 05060708h, 0A0B0C0Dh
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
        
        mov ebx, eax
        mov dl, al 
        movsx dx, dl 
        and eax, 00FF0000h
        shr eax, 16
        movsx ax, al 
        add ax, dx ; cuvantul low 
        mov dl, bh 
        movsx dx, dl 
        and ebx, 0FF000000h
        shr ebx, 24 
        movsx bx, bl 
        add bx, dx 
        shl ebx, 16 ; cuvantul high
        or eax, ebx 
        stosd
        
        inc ecx
        jmp parucrugere
        stop:
        push    dword 0      
        call    [exit]      
    
