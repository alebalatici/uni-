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
    mod_acces db 'r', 0 
    len equ 100
    text times (len+1) db 0 
    descriptor_fis dd -1
    format dd "y apare de %d ori si z apare de %d ori.", 0 
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
        
        mov [cnt], eax 
        mov ecx, 0
        mov ebx, 0
        mov edx, 0
        parcurgere:
        cmp ecx, [cnt]
        jge stop
        mov al, [text+ecx] 
        cmp al, 'y'
        je gasity
        cmp al, 'z'
        je gasitz
        jmp finish
        gasity:
        inc ebx  
        jmp finish
        gasitz:
        inc edx 
        finish:
        inc ecx 
        jmp parcurgere
        stop:
        push dword edx 
        push dword ebx 
        push dword format 
        call [printf]
        add esp, 12
        
        push dword [descriptor_fis]
        call fclose
        add esp, 4
        final:
        push    dword 0      
        call    [exit]       
