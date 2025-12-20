bits 32 
global start   
extern exit, printf, scanf, fopen, fread, fclose
import exit msvcrt.dll  
import printf msvcrt.dll  
import scanf msvcrt.dll
import fopen msvcrt.dll 
import fread msvcrt.dll
import fclose msvcrt.dll 
segment data use32 class=data
    nume_fisier db "input.txt", 0 
    mod_acces db "r", 0 
    descriptor_fis dd -1
    len equ 100 ; numarul maxim de elemente citite din fisier
    text times len db 0 ; sirul in care se va iesi textul din fisier 
    format db "Numarul cu frecventa maxima este: %d", 10, 0
    baza_10 db "%d", 0 
    cnt dd 0 
    frecventa times 10 db 0 
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 8
        
        mov [descriptor_fis], eax 
        cmp eax, 0 
        je final
        
        push dword [descriptor_fis]
        push dword len 
        push dword 1
        push dword text 
        call [fread]
        add esp, 16 
        
        mov [cnt], eax
        mov ecx, 0 
        parcurgere:
        cmp ecx, [cnt]
        jge stop
        mov al, [text+ecx]
        cmp al, '0'
        jl finish
        cmp al, '9'
        jg finish
        sub al, '0'
        movzx eax, al 
        mov bl, [frecventa+eax]
        inc bl 
        mov [frecventa+eax], bl 
        finish:
        inc ecx 
        jmp parcurgere
        stop:
        
        mov edx, 0
        mov ecx, 0
        mov edi, 0
        parcurgere1:
        cmp ecx, 10 
        jge stop1
        mov bl, [frecventa+ecx]
        cmp bl, dl 
        jle finish1
        mov dl, bl
        mov edi, ecx 
        finish1:
        inc ecx 
        jmp parcurgere1
        
        stop1:
        push dword edi 
        push dword format
        call [printf]
        add esp, 8 
        final:
        push    dword 0      
        call    [exit]   