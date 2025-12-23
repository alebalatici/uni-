bits 32
global start
extern exit, fopen, fgets, fclose, printf, fread, scanf, gets, fprintf, sprintf 
import exit msvcrt.dll
import fopen msvcrt.dll
import fgets msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
import scanf msvcrt.dll 
import gets msvcrt.dll
import fprintf msvcrt.dll 
import sprintf msvcrt.dll 
segment data use32 class=data
    filename db "input.txt",0       
    read dd "r", 0 
    write dd "w", 0 
    addition dd "a", 0 
    text times 101 db 0 
    len equ 100
    descriptor_fis dd -1
    const dd 0 
    newline dd 10, 0
    baza_10 dd "%d", 0
    text_error db "Numar prea mare", 0 
    n dd  0
    format dd "output-%d.txt"
    sir db 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    l equ ($-sir)
    dynamic_filename times 100 db 0 
segment code use32 class=code
start:
    push dword n 
    push dword baza_10
    call [scanf] 
    add esp, 8 
    
    cmp dword [n], 255
    ja errorr
    
    mov ecx, [n]
    parcurgere:
    mov [const], ecx 
        
        push ecx 
        push dword format
        push dword dynamic_filename
        call [sprintf]
        add esp, 12
        
        push dword write 
        push dword dynamic_filename 
        call [fopen] 
        add esp, 12
        
        mov [descriptor_fis], eax 
        cmp eax, 0 
        je final
        
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4
        
    mov ecx, [const]
    dec ecx 
    jnz parcurgere
    
    jmp final 
    errorr:
    push dword text_error
    call [printf]
    add esp, 4
    
    final:
    push dword 0
    call [exit]
