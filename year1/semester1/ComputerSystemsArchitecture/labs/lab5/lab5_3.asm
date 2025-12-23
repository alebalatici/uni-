; Two byte strings S1 and S2 are given. Obtain the string D by concatenating the elements of S1 from the left hand side to the right hand side and the elements of S2 from the right hand side to the left hand side.
bits 32 
global start        
extern exit             
import exit msvcrt.dll  
segment data use32 class=data
    s1 db 1, 2, 3, 4
    l1 equ ($-s1)
    s2 db 5, 6, 7
    l2 equ ($-s2)
; D: 1, 2, 3, 4, 7, 6, 5
    d resb l1 + l2
segment code use32 class=code
    start:
        mov esi, s1
        mov edi, d
        mov ecx, l1
        copiere_s1:
        mov al, [esi]
        mov [edi], al
        inc esi
        inc edi
        loop copiere_s1
        mov esi, s2
        add esi, l2-1
        mov ecx, l2
        
        copiere_s2:
        mov al, [esi]
        mov [edi], al
        dec esi
        inc edi
        loop copiere_s2
        call    [exit]       
