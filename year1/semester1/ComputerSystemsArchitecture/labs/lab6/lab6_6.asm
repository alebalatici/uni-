bits 32
global start        
extern exit   
extern printf           
import exit msvcrt.dll   
import printf msvcrt.dll  
segment data use32 class=data
s dw -22, 145, -48, 127
len equ ($ - s)/2
d times len resb 1
segment code use32 class=code
start:
    mov esi, s 
    mov edi, d 
    mov ecx, len
    
    parcurgere:
        cmp ecx, 0 
        je final 
        
        lodsw
        
        movsx eax, ax 
        push eax 
        
        mov bl, 16 
        mov edx, 0 
        inner_loop:
            cmp bl, 0 
            je final_inner_loop
        
            shr ax, 1
            adc edx, 0 
        
            dec bl 
            jmp inner_loop
            
        final_inner_loop:
        pop eax 
        cmp ax, 0 
        jl negativ
        
        ;pozitiv
        mov al, dl 
        stosb 
        jmp urm
        
        negativ:
        mov al, 16
        sub al, dl 
        stosb 
 
        urm:
        dec ecx 
        jmp parcurgere
    
    
    final:
    call [exit]
