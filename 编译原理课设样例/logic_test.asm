section .data
section .text
global main

main:
    push ebp
    mov ebp, esp
    sub esp, 64
    mov dword [ebp-4], 10
    mov dword [ebp-8], 20
    mov dword [ebp-12], 0
    mov eax, [ebp-4]
    cmp eax, 5
    setg al
    movzx eax, al
    mov [ebp-16], eax
    mov eax, [ebp-8]
    cmp eax, 30
    setl al
    movzx eax, al
    mov [ebp-20], eax
    mov eax, [ebp-24]
    test eax, eax
    jz L0
    mov dword [ebp-28], 1
L0:
    mov eax, [ebp-4]
    cmp eax, 5
    setl al
    movzx eax, al
    mov [ebp-32], eax
    mov eax, [ebp-8]
    cmp eax, 15
    setg al
    movzx eax, al
    mov [ebp-36], eax
    mov eax, [ebp-40]
    test eax, eax
    jz L2
    mov dword [ebp-28], 2
L2:
    mov eax, [ebp-44]
    test eax, eax
    jz L4
    mov dword [ebp-28], 3
L4:
    mov eax, [ebp-48]
    test eax, eax
    jz L6
    mov dword [ebp-28], 4
L6:
    mov eax, [ebp-4]
    cmp eax, 0
    setl al
    movzx eax, al
    mov [ebp-52], eax
    mov eax, [ebp-56]
    cmp eax, 0
    setg al
    movzx eax, al
    mov [ebp-60], eax
    mov eax, [ebp-64]
    test eax, eax
    jz L8
    mov dword [ebp-28], 5
L8:
    mov eax, [ebp-68]
    cmp eax, 0
    setg al
    movzx eax, al
    mov [ebp-72], eax
    mov eax, [ebp-76]
    test eax, eax
    jz L10
    mov dword [ebp-28], 6
L10:
    mov eax, [ebp-28]
    mov esp, ebp
    pop ebp
    ret
