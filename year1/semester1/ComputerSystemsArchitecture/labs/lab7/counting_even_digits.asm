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
    format db "Numarul de numere pare este: %d", 10, 0
    baza_10 db "%d", 0 
    cnt dd 0 
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
        mov edx, 0 
        parcurgere:
        cmp ecx, [cnt] 
        jge stop
        mov al, [text+ecx]
        cmp al, '0'
        jl finish 
        cmp al, '9'
        jg finish
        sub al, '0'
        test al, 01h
        jnz finish; impar 
        inc edx 
        finish:
        inc ecx 
        jmp parcurgere
        stop:
        
        push dword edx 
        push dword format 
        call [printf]
        add esp, 8 
        final:
        push    dword 0      
        call    [exit]         
