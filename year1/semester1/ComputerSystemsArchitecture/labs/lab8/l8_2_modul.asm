; l8_2_main.asm + l8_2_modul.asm
bits 32
global citire_afisare
segment code use32 class=code
citire_afisare:
    parcurgere:
            push dword nr 
            push dword frm_int
            call [scanf]
            add esp, 8
            
            cmp eax, 1 
            jne final
           
            push dword [nr]
            push frm_print
            call [printf]
            add esp, 8 
            
            inc ebx
            jmp parcurgere
        final:
        ret