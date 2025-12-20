bits 32 
global start   
extern exit, printf, scanf, fopen, fread, fclose, fprintf, fgets
import exit msvcrt.dll  
import printf msvcrt.dll  
import scanf msvcrt.dll
import fopen msvcrt.dll 
import fread msvcrt.dll
import fclose msvcrt.dll 
import fprintf msvcrt.dll 
import fgets msvcrt.dll 
segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces db "w", 0 
    mod_acces1 db "a", 0 
    descriptor_fis dd -1
    text resb 120 
    format db "%s", 0
    spatiu db " ", 0
segment code use32 class=code
    start:
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 8
        
        mov [descriptor_fis], eax 
        cmp eax, 0 
        je final
        
        push dword text 
        push dword format
        call [scanf]
        add esp, 8 
        mov al, [text] 
        
        push dword text
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 8 
        
        parcurgere:
        cmp al, '$'
        jz stop 
        
        push dword text 
        push dword format
        call [scanf]
        add esp, 8
        mov al, [text]
        
        push dword spatiu
        push dword text 
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 8 
        
        mov al, [text]
        jmp parcurgere
        
        stop:
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4 
        final:
        push    dword 0      
        call    [exit]       
