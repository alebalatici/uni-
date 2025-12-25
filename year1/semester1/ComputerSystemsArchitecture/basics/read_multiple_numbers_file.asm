bits 32
global start
extern exit, fopen, fclose, fscanf, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll
segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces   db "r", 0
    fmt_int     db "%d", 0        ; format pentru citire
    fmt_print   db "Poz %d: %d", 10, 0
    descriptor_fis dd 0
    nr dd 0                       ; aici se va salva numarul citit
segment code use32 class=code
    start:
    ; fopen("input.txt", "r")
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp, 8

    cmp eax, 0
    je final
    mov [descriptor_fis], eax
    
    mov ebx, 0 ; index pt pozitie
    citire:
        ; fscanf(descriptor, "%d", &nr)
        push dword nr
        push dword fmt_int
        push dword [descriptor_fis]
        call [fscanf]
        add esp, 12

        cmp eax, 1              ; eax = 1 daca s-a gasit un numar
        jne gata                ; altfel s-a terminat

        ; printf("Poz %d: %d\n", poz, nr)
        push dword [nr]
        push dword ebx 
        push dword fmt_print
        call [printf]
        add esp, 12
        
        inc ebx 
        jmp citire

        gata:
        ; fclose(descriptor)
        push dword [descriptor_fis]
        call [fclose]
        add esp, 4

    final:
    push dword 0
    call [exit]

