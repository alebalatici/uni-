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
    yes db "%d este patrat perfect", 0  
    no db "%d nu este patrat perfect", 0 
segment code use32 class=code
    start:
        push dword n 
        push dword frm_int
        call [scanf]
        add esp, 8
        
        mov eax, 0 
        perfect_square_loop:
            push eax 
            mov edx, 0 
            mul eax 
            cmp eax, [n]
            je perfect_square 
            jg not_perfect_square
            pop eax 
            inc eax 
            jmp perfect_square_loop
            
        perfect_square:
            push dword [n]
            push dword yes 
            call [printf]
            add esp, 8
            jmp stop
            
        not_perfect_square:
            push dword [n]
            push dword no 
            call [printf]
            add esp, 8             
            
        stop:
        push    dword 0     
        call    [exit]    
