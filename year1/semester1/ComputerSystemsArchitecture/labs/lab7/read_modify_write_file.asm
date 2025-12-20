; reads text from file, replaces spaces with 'S' and writes the modified text back to the file
bits 32
global start
extern exit, fopen, fgets, atoi, fclose, printf, fread, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fgets msvcrt.dll
import atoi msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
segment data use32 class=data
    filename db "input.txt", 0       ; fișierul cu numărul
    read dd "r", 0 
    write dd "w", 0 
    text times 101 db 0 
    len equ 100
    descriptor_fis dd -1
    const dd 0
segment code use32 class=code
start:
    push dword read 
    push dword filename
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
    
    mov [const], eax 
    
    push dword [descriptor_fis]
    call [fclose]
    add esp, 4 
    
    mov ebx, 0 
    parcurgere:
    cmp ebx, [const]
    jge finish 
    
    mov al, [text + ebx] 
    cmp al, ' ' 
    jne urmatorul
    mov byte [text + ebx], 'S'
    urmatorul:
    inc ebx 
    jmp parcurgere
    finish:
    
    push dword write
    push dword filename 
    call [fopen]
    add esp, 8 
    
    mov [descriptor_fis], eax 
    cmp eax, 0 
    je final
    
    push dword text
    push dword [descriptor_fis]
    call [fprintf]
    add esp, 8
    
    push dword [descriptor_fis]
    call [fclose] 
    add esp, 4
    
    final:
    push dword 0
    call [exit]
