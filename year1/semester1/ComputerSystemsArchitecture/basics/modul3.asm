global _asm_modify_int
segment data use32 class=data
segment code use32 class=code
_asm_modify_int:
    push ebp
    mov ebp, esp 
    
    mov esi, [ebp + 8]
    mov ecx, [ebp + 12]
    
    modify:
        cmp ecx, 0 
        je final
        
        mov eax, [esi]
        add eax, 1
        mov [esi], eax 
        
        add esi, 4
        dec ecx 
        jmp modify
        
    final:
        pop ebp 
        ret