bits 32
global _aduna
segment data use32 class=data
segment code use32 class=code
_aduna:
        mov eax, [esp + 4]
        mov ebx, [esp + 8]
        add eax, ebx
        ret
        
