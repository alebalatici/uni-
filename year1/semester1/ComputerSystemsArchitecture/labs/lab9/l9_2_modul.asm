//l9_2_main.c + l9_2_modul.asm 
global _adaugare_asm
segment code use32 class=code
_adaugare_asm:
    push ebp
    mov ebp, esp 
    
    ;adaugare_asm(x, sir[], len)
    mov eax, [ebp + 8] ;x
    mov edx, [ebp + 12] ; sir
    mov ecx, [ebp + 16] ; pointer len
    
    mov ebx, [ecx]
    mov [edx + ebx * 4], eax ; sir[len] = x  
    inc ebx 
    mov [ecx], ebx 
    
    pop ebp 
    ret

