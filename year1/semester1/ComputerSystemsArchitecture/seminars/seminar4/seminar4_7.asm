;7. Se dă un unui șir de octeți reprezentând un text (o succesiune de șiruri de caractere separate prin spații).
;Să se determine cuvintele din șir care sunt palindroame (ex. cojoc, capac etc.).
bits 32
global start        
extern exit       
import exit msvcrt.dll    

segment data use32 class=data
text db "cojoc nivel radar nivel rotator test", 0
l equ ($-text)
d resb l

segment code use32 class=code
start:
    mov ecx, 0        ; index în text
    mov ebp, 0        ; index în d
    mov edi, 0
    
    parcurgere:
    cmp ecx, l
    jge stop
    mov al, [text+ecx]
    cmp al, ' '
    je inc_ecx
    ; început cuvânt
    mov edx, ecx
    inc edx
    
    parcurgere1:
    mov al, [text+edx]
    cmp al, ' '
    je gasit
    cmp al, 0
    je gasit
    inc edx
    jmp parcurgere1
    
    gasit:
    dec edx           ; edx = ultimul caracter
    push edx
    mov esi, ecx
    
    parcurgere2:
    mov al, [text+esi]
    mov bl, [text+edx]
    cmp al, bl
    jne urmatorul
    inc esi
    dec edx
    cmp esi, edx
    jle parcurgere2   ; corect pentru egalitate
    ; palindrom găsit
    pop edx
    mov esi, ecx
    
    copiere:
    cmp esi, edx
    jg add_space
    mov al, [text+esi]
    mov [d+ebp], al
    inc ebp
    inc esi
    jmp copiere
    
    add_space:
    mov byte [d+ebp], ' '
    inc ebp
    
    urmatorul:
    mov al, [text+edx]
    cmp al, 0
    je stop
    inc edx
    mov ecx, edx
    jmp parcurgere
    
    inc_ecx:
    inc ecx
    jmp parcurgere
    
    stop:
    push dword 0
    call [exit]