global _bin_to_hex

segment data use32 class=data

segment code use32 class=code
_bin_to_hex:
    push ebp
    mov ebp, esp

    mov esi, [ebp + 8]    ; pointer la string binar
    xor eax, eax          ; rezultatul = 0

convert:
    mov bl, [esi]
    cmp bl, 0
    je final              ; sfârșit string

    shl eax, 1            ; eax *= 2

    cmp bl, '1'
    jne skip_add
    add eax, 1

skip_add:
    inc esi
    jmp convert

final:
    pop ebp
    ret
