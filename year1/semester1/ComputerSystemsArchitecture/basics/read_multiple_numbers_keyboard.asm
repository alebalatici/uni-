bits 32 
global start        
extern exit, scanf, printf
import exit msvcrt.dll  
import scanf msvcrt.dll 
import printf msvcrt.dll
segment data use32 class=data
    nr dd 0 
    frm_int db "%d", 0 
    fmt_print db "Poz %d: %d", 10, 0
    aux dd 0 
segment code use32 class=code
    start:
        mov ebx, 0 
        citire:
            mov [aux], ebx 
            push dword nr 
            push dword frm_int
            call [scanf]
            add esp, 8
            
            cmp eax, 1 
            jne final
            
            mov ebx, [aux]
           
            push dword [nr]
            push dword ebx 
            push fmt_print
            call [printf]
            add esp, 12 
            
            inc ebx 
            
            jmp citire
            
        final:
        push dword 0
        call    [exit]       