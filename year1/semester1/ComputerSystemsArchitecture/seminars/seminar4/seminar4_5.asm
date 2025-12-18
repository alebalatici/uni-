;5. Se dau două șiruri de octeți S1 și S2 de lungimi egale. Să se determine poziția p în care elementele
;ambelor șiruri sunt egale.
bits 32
global start        
extern exit        
import exit msvcrt.dll   
segment data use32 class=data
    s1 db 2, 3, 1, 7, 6, 9, 2, 8
    l equ ($-s1)
    s2 db 1, 2, 5, 6, 8, 9, 2, 0
segment code use32 class=code
start:
        mov ecx, 0
        mov esi, s1 
        mov edi, s2
        
        parcurgere:
        lodsb ; al = esi[index]
        mov bl, [s2+ecx]
        cmp al, bl
        jnz nu_sunt_egale
        jmp gata
        
        nu_sunt_egale:
        inc edi
        inc ecx
        cmp ecx, l
        jnz parcurgere
        
        gata:
        ;inc ecx daca indexul este de la 1
        mov eax, ecx
        ;rezultatul final este in eax 
        push dword 0
        call [exit]