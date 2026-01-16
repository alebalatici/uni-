bits 32 
global start        
extern exit, printf, scanf                
import exit msvcrt.dll   
import printf msvcrt.dll
import scanf msvcrt.dll
segment data use32 class=data
    frm db "%s", 0 
    frm_int db "%d", 0
    n dd 0
    r dd 0 
segment code use32 class=code
    start:
        push dword n 
        push dword frm_int
        call [scanf]
        add esp, 8
        
        mov eax, 0 
        square_root:
            push eax 
            mov edx, 0 
            mul eax 
            cmp eax, [n]
            je patrat_perfect
            jg radical 
            pop eax 
            inc eax 
            jmp square_root
            
        patrat_perfect:
            pop eax 
            mov [r], eax 
            jmp afisare
            
        radical:
            pop eax 
            dec eax 
            mov [r], eax 
            
        afisare:
            push dword [r]
            push dword frm_int
            call [printf]
            add esp, 8
        
        push    dword 0   
        call    [exit]   
