; l8_2_main.asm + l8_2_modul.asm
bits 32 
global start        
extern exit, scanf, printf
import exit msvcrt.dll  
import scanf msvcrt.dll 
import printf msvcrt.dll
%include "l8_2_modul.asm"
segment data use32 class=data
    nr dd 0 
    frm_int db "%d", 0 
    frm_print db "%d ", 0
    aux dd 0 
segment code use32 class=code
    start:
        call citire_afisare
        push dword 0
        call    [exit]       