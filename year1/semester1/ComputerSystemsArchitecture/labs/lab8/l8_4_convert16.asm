; l8_4_main.asm + l8_4_convert16.asm + l8_4_convert2.asm
global convertire16
segment code use32 class=code
convertire16: 
    mov ecx, 16 
    mov ebx, 0 
    convert16:
        cmp eax, 0 
        je final16 
        
        mov edx, 0 
        div ecx 
        
        cmp edx, 10 
        jge letter
        add edx, '0'
        jmp store
        
        letter:
        add edx, 'a'-10
        
        store:
        mov byte [aux + ebx], dl
        inc ebx 
        jmp convert16
    final16:
    mov byte [aux + ebx], 0 
    
    dec ebx 
    mov edx, 0 
    inversare16:
        mov al, [aux + ebx]
        mov byte [base16 + edx], al
        inc edx 
        dec ebx
        jns inversare16 
    mov byte [base16 + edx], 0  
    ret
