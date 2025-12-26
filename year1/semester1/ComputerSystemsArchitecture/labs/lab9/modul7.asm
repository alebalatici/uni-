global _asm_create
segment code use32 class=code

_asm_create:
    push ebp
    mov ebp, esp
    push esi
    push edi
    push ebx

    mov esi, [ebp + 8]    ; pointer la source
    mov edi, [ebp + 12]   ; pointer la sir1 (litere mari)
    mov ebx, [ebp + 16]   ; pointer la sir2 (litere mici)

   parcurgere:
    lodsb
    cmp al, 0
    je final
    ;dec al
    cmp al, 'A'
    jl check_litera_mica
    cmp al, 'Z'
    jg check_litera_mica
  
    ;inc al
    stosb           
    jmp parcurgere

check_litera_mica:
    cmp al, 'a'
    jl parcurgere
    cmp al, 'z'
    jg parcurgere
  
    ;inc al
    mov [ebx], al
    inc ebx
    jmp parcurgere

final:
    mov byte [edi], 0
    mov byte [ebx], 0


    pop ebx
    pop edi
    pop esi
    pop ebp
    ret
