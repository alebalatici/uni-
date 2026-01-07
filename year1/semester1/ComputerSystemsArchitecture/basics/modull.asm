global _asm_modify
segment data use32 class=data
segment code use32 class=code
_asm_modify:
    push ebp
    mov ebp, esp 
    
    mov esi, [ebp + 8]; sirul sursa
    
    modify:
        mov al, [esi]
        cmp al, 0
        je final
        
        add al, 1 
        mov [esi], al
        
        inc esi 
        jmp modify
        
    final:
        pop ebp 
        ret 
        
    
        
    
