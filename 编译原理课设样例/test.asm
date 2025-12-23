section .data
section .text
global main

main:
    push ebp
    mov ebp, esp
    sub esp, 64
    mov dword [ebp-4], 10
    mov dword [ebp-8], 20
    mov eax, [ebp-4]
    cmp eax, dword [ebp-8]
    setl al
    movzx eax, al
    mov [ebp-12], eax
    mov eax, [ebp-12]
    test eax, eax
    jz L0
    mov dword [ebp-16], 30
    mov dword [ebp-4], 60
L0:
L2:
    mov eax, [ebp-4]
    cmp eax, 0
    setg al
    movzx eax, al
    mov [ebp-20], eax
    mov eax, [ebp-20]
    test eax, eax
    jz L3
    mov dword [ebp-8], 21
    mov dword [ebp-4], 9
    jmp L2
L3:
    mov eax, 0
    mov esp, ebp
    pop ebp
    ret
