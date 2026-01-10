bits 32 
global start   
extern exit  
extern printf 
extern scanf          
import exit msvcrt.dll  
import printf msvcrt.dll 
import scanf msvcrt.dll  
segment data use32 class=data
    s resd 1
    frm_int db "%d", 0 
segment code use32 class=code
    start:
        push dword s 
        push dword frm_int
        call [scanf]
        add esp, 8 
        
        cmp [s], dword 2
        jb not_prime
        
        je prime
        
        mov ecx, [s]
        mov edx, 0 
        shr ecx, 1
        adc edx, 0 
        cmp edx, 0 
        je not_prime
        
        mov ecx, 3
        mov eax, [s]
        
        verificare:
            cmp ecx, eax 
            jge prime 
            
            mov edx, 0 
            div ecx 
            
            cmp edx, 0 
            je not_prime
            
            mov eax, [s] 
            add ecx, 2 
            jmp verificare
        
        not_prime:
            mov eax, 0 
            jmp final 
            
        prime:
            mov eax, [s] 
        
        final:
        push dword eax 
        push dword frm_int
        call [printf]
        add esp, 8 
        
        push    dword 0     
        call    [exit]      