bits 32
global start
extern exit, fopen, fgets, fclose, printf, fread, scanf, gets, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fgets msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
import scanf msvcrt.dll 
import gets msvcrt.dll
import fprintf msvcrt.dll 
segment data use32 class=data
    filename db "input.txt",0       ; fișierul cu numărul
    read dd "r", 0 
    write dd "w", 0 
    text times 101 db 0 
    len equ 100
    descriptor_fis dd -1
    const dd 0 
segment code use32 class=code
start:
    push dword write
    push dword filename
    call [fopen]
    add esp, 8 
    
    mov [descriptor_fis], eax 
    cmp eax, 0 
    je final
    
    push dword text 
    call [gets] 
    add esp, 4 
    
    push dword text
    push dword [descriptor_fis]
    call [fprintf]
    add esp, 4 
    
    push dword [descriptor_fis]
    call [fclose]
    add esp, 4 
    final:
    push dword 0
    call [exit]
