bits 32
global start        
extern exit   
extern printf           
import exit msvcrt.dll   
import printf msvcrt.dll  
segment data use32 class=data
sir dd 0702090Ah, 0B0C0304h, 05060108h
len equ ($-sir) / 4
s times len*2 resb 1;72h, 9Ah, 0BCh,  34h, 56h, 18h
segment code use32 class=code
start:
    mov ecx, len 
    mov esi, sir
    mov edi, s 
    
    parcurgere:
        cmp ecx, 0 
        je final 
        
        lodsd 
        
        mov ebx, eax 
        shr ebx, 16 
        
        shl bl, 4
        shr bx, 4
        
        shl al, 4
        shr ax, 4
        
        mov dl, al 
        mov al, bl
        stosb 
        
        mov al, dl 
        stosb
        
        dec ecx 
        jmp parcurgere
        
   final:
   
   mov ecx, len 
   add ecx, len 
   dec ecx 
   outer_loop:
        mov esi, 0 
        mov edx, ecx 
        
        inner_loop:
            mov al, [s + esi]
            mov bl, [s + esi + 1]

            cmp al, bl 
            jng no_swap
            
            ;swap
            mov [s + esi + 1], al 
            mov [s + esi], bl 
            
            no_swap:
                inc esi 
                dec edx 
                jnz inner_loop
                
            dec ecx 
            jnz outer_loop
   
   call [exit]