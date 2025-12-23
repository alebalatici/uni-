;BUBBLE SORT NASM x86, 32 bits
;https://www.youtube.com/watch?v=-oRYa1gg3nU
bits 32
global start        
extern exit        
import exit msvcrt.dll   
segment data use32 class=data
    s db 2, 3, 1, 7, 6, 9, 2, 8
    l equ ($-s)
    d resb l
segment code use32 class=code
	start:
        mov ecx, l
        dec ecx; de la 0 la al l-1-lea element
    outer_loop:
        mov esi, 0; indexul curent
        mov edx, ecx; va fi numarul total de comparatii
        ; pentru ecx = l-1(primul element) va trebui sa il comparam cu toate (restul) cele l-1 elemente
    inner_loop:
        mov al, [s+esi]
        mov bl, [s+esi+1]
        cmp al, bl
        jbe no_swap
        ;swap
        mov [s+esi], bl
        mov [s+esi+1], al
    no_swap:
        inc esi
        dec edx
        jnz inner_loop 
        dec ecx
        jnz outer_loop 
        push    dword 0    
        call    [exit]       
