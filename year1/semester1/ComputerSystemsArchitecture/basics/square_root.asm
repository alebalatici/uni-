bits 32 
global start        
extern exit
extern scanf 
extern printf 
import exit msvcrt.dll   
import scanf msvcrt.dll
import printf msvcrt.dll  
segment data use32 class=data
    s resd 1
    frm db "%d", 0 
    frm_print_yes db "Este patrat perfect: %d", 0
    frm_print_no db "Nu este patrat perfect: %d", 0
segment code use32 class=code
    start:
        push dword s 
        push dword frm 
        call [scanf]
        add esp, 8
        
        cmp [s], dword 0
        jne not_zero
        
        push dword [s]
        push dword frm_print_yes
        call [printf]
        add esp, 8
        
        jmp stop
        
        not_zero:
            mov eax, 0 
            parcurgere:
                push eax 
                mov edx, 0 
                mul eax 
                
                cmp eax, [s] 
                je final
                
                jg nu_e_sq
                
                pop eax 
                inc eax 
                jmp parcurgere
            
            nu_e_sq:
            mov eax, 0 
            
            final:
                cmp eax, 0 
                jne is_perfect_square
                
                push dword eax 
                push dword frm_print_no 
                call [printf]
                add esp, 8
                jmp stop 
            
            is_perfect_square:
                push dword eax 
                push dword frm_print_yes
                call [printf]
                add esp, 8 
                
        stop:
        push    dword 0     
        call    [exit]     