bits 32 
global start        
extern printf 
extern exit             
import exit msvcrt.dll 
import printf msvcrt.dll    
segment data use32 class=data
    a dd 16 ; convertire in baza 16 
    s times 10 db 0 
    rez times 10 db 0 
    format db "%s", 0 
segment code use32 class=code
    start:
        mov ecx, 16
        mov eax, [a]
        mov ebx, 0 
        
        impartire:
        cmp eax, 0 
        je stop
        
        mov edx, 0 
        div ecx 
        cmp edx, 10
        jl completare
        
        sub edx, 10 
        add edx, 'A' ; 'a' pentru litere mici
        jmp store
        
        completare:
        add edx, '0'
        
        store:
        mov byte  [s + ebx], dl 
        inc ebx 
        jmp impartire
        stop:
        
        mov byte [s + ebx], 0 ; gata sirul
        
        dec ebx 
        mov ecx, 0 
        inversare:
        mov al, [s + ebx] 
        mov byte [rez + ecx], al 
        inc ecx 
        dec ebx 
        jns inversare ; echivalent cu jmp while ebx >= 0 
        
        mov byte [rez + ecx], 0 
        
        push dword rez  
        push dword format
        call [printf]
        add esp, 8
        
        push    dword 0      
        call    [exit]    
