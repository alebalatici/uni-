; l9_5_main.c + l9_5_modul.asm
bits 32
global _asm_calcul

segment code use32 class=code
_asm_calcul:
   

    mov eax, [esp+4]    ; a
    add eax, [esp+8]    ; a + b
    sub eax, [esp+12]   ; a + b - c

    ret

