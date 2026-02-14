bits 32
global start        
extern exit   
extern printf           
import exit msvcrt.dll   
import printf msvcrt.dll  
segment data use32 class=data
s DB 01011100b, 10001001b, 11100101b
len equ ($ - s)
d times len resb 1
segment code use32 class=code
start:

    std 
	mov esi, s + len - 1
    mov ecx, 0 
    parcurgere:
        cmp ecx, len
        je final
        
        lodsb
        
        mov [d + ecx], al 
        
        inc ecx 
        jmp parcurgere
	
final:
   call [exit]