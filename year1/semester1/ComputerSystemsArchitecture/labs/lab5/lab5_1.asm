; Given a byte string S of length l, obtain the string D of length l-1 as D(i) = S(i) * S(i+1) (each element of D is the product of two consecutive elements of S).
bits 32 
global start        
extern exit             
import exit msvcrt.dll  
segment data use32 class=data
s db 1, 2, 3, 4; sirul initial
; d = [2, 6, 12]
l equ ($-s); lungimea sirului (4)
d resb l-1
segment code use32 class=code
    start:
        mov esi, s; adresa sirului s (source)
        mov edi, d; adresa sirului d (destinatie)
        mov ecx, l-1
        din_nou:
            mov al, [esi]
            mov bl, [esi+1]
            mul bl 
            mov [edi], al
            inc esi
            inc edi
            loop din_nou
        call    [exit]       
