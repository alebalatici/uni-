; reads a text, creates a file with the given name in lowercase letters, writes the text to the file in lowercase letters
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
    nume_fisier resb 30
    mod_acces db "w", 0 
    mod_acces1 db "a", 0 
    descriptor_fis dd -1
    text resb 120 
    format db "%s", 0
    cnt dd 0 
segment code use32 class=code
    start:
        push nume_fisier
        push format
        call [scanf]
        add esp, 8
        
        mov ecx, 0 
        parucrgere:
        mov al, [nume_fisier+ecx]
        cmp al, 0
        je stop 
        cmp al, 'A'
        jl finish
        cmp al, 'Z'
        jg finish 
        add al, 32
        mov [nume_fisier+ecx], al 
        finish:
        inc ecx 
        jmp parucrgere
        stop:
        
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 8
        
        mov [descriptor_fis], eax 
        cmp eax, 0 
        je final
       
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4 
        
        push dword mod_acces1
        push dword nume_fisier
        call [fopen]
        add esp, 8
        
        mov [descriptor_fis], eax 
        cmp eax, 0 
        je final
        
        push dword nume_fisier
        push dword [descriptor_fis]
        call [fprintf]
        add esp, 8
        
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4 
        
        final:
        push    dword 0      
        call    [exit]       