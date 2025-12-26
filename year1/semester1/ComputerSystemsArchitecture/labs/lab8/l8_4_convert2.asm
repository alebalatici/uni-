; l8_4_main.asm + l8_4_convert16.asm + l8_4_convert2.asm
global convertire2
segment code use32 class=code
convertire2:
    mov ecx, 2 
    mov ebx, 0 
    convert2:
        cmp eax, 0 
        je final2
        
        mov edx, 0  
        div ecx 
        
        add dl, '0'
        mov byte [aux + ebx], dl 
        inc ebx 
        jmp convert2
    final2:
    mov byte [aux + ebx], 0
    
    dec ebx 
    mov edx, 0 
    inversare2:
        mov al, [aux + ebx] 
        mov byte [base2 + edx], al 
        inc edx
        dec ebx 
        jns inversare2
    mov byte [base2 + edx], 0 
    ret 
        
        