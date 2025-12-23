; Given a character string S, obtain the string D containing all special characters (!@#$%^&*) of the string S.
bits 32 
global start        
extern exit             
import exit msvcrt.dll  
segment data use32 class=data
s db '+', '4', '2', 'a', '@', '3', '$', '*'; sirul initial
; d = '@','$','*', caractere speciale = ! @ # $ % ^ & *
l equ ($-s); lungimea sirului (4)
d resb l+1
segment code use32 class=code
    start:
        mov esi, s; adresa sirului s (source)
        mov edi, d; adresa sirului d (destinatie)
        mov ecx, l; numarul de caractere al sirului s   
        test ecx, ecx
        jz finish   
        din_nou:
            mov al, [esi]
        cmp al, '!'
        je adauga
        cmp al, '@'
        je adauga
        cmp al, '#'
        je adauga
        cmp al, '$'
        je adauga
        cmp al, '%'
        je adauga
        cmp al, '^'
        je adauga
        cmp al, '&'
        je adauga
        cmp al, '*'
        je adauga        
        inc esi; i++ !
        dec ecx; i++ !
        jnz din_nou; ecx != 0 => din_nou (sau urmatorul element) !
        jmp finish; ecx = 0 => ?        
        adauga:
        mov [edi], al; am gasit un caracter special
        inc edi; ind++ 
        inc esi; i++ !
        dec ecx; i++ !
        jnz din_nou; urmatorul caracter !
        finish:
            mov byte [edi], 0
        call    [exit]       
