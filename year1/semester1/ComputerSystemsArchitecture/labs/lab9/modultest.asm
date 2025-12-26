; asm_concat.asm
; NASM 32-bit, cdecl, Windows
global _asm_concat

section .text
_asm_concat:
    push ebp
    mov ebp, esp

    mov esi, [ebp + 12]    ; s1
    mov edi, [ebp + 8]     ; rez

.copy_s1:
    mov al, [esi]
    mov [edi], al
    cmp al, 0
    je .copy_s2
    inc esi
    inc edi
    jmp .copy_s1

.copy_s2:
    mov esi, [ebp + 16]    ; s2
.copy_s2_loop:
    mov al, [esi]
    mov [edi], al
    cmp al, 0
    je .done
    inc esi
    inc edi
    jmp .copy_s2_loop

.done:
    pop ebp
    ret
