; x86 (32-bit) assembly emitted from IR
extern printf
extern scanf
section .data
fmt_read  db "%d", 0
fmt_write db "%d", 10, 0
section .text
global main
main:
    push ebp
    mov ebp, esp
    sub esp, 96
    mov eax, 3
    mov ebx, 4
    add eax, ebx
    mov [ebp-24], eax
    mov eax, [ebp-24]
    mov [ebp-4], eax
    mov eax, [ebp-24]
    mov ebx, 2
    imul eax, ebx
    mov [ebp-56], eax
    mov eax, [ebp-56]
    mov ebx, 5
    sub eax, ebx
    mov [ebp-60], eax
    mov eax, [ebp-60]
    mov [ebp-8], eax
    mov eax, [ebp-60]
    cdq
    mov ebx, 4
    idiv ebx
    mov [ebp-64], edx
    mov eax, [ebp-64]
    mov [ebp-12], eax
    mov eax, 3
    mov ecx, 4
    mov ebx, 1
    cmp ecx, 0
    jl pow_done_0
pow_loop_0:
    cmp ecx, 0
    je pow_done_0
    imul ebx, eax
    dec ecx
    jmp pow_loop_0
pow_done_0:
    mov eax, ebx
    mov [ebp-68], eax
    ; READ t5
    lea eax, [ebp-68]
    push eax
    push fmt_read
    call scanf
    add esp, 8
    ; WRITE t1
    mov eax, [ebp-24]
    push eax
    push fmt_write
    call printf
    add esp, 8
    ; WRITE t5
    mov eax, [ebp-68]
    push eax
    push fmt_write
    call printf
    add esp, 8
    mov eax, [ebp-24]
    mov ebx, [ebp-68]
    imul eax, ebx
    mov [ebp-72], eax
    ; WRITE t6
    mov eax, [ebp-72]
    push eax
    push fmt_write
    call printf
    add esp, 8
    mov eax, 3
    mov ebx, 4
    cmp eax, ebx
    setl al
    movzx eax, al
    mov [ebp-76], eax
    mov eax, [ebp-76]
    cmp eax, 0
    je L4
    mov eax, [ebp-8]
    mov ebx, [ebp-4]
    cmp eax, ebx
    setge al
    movzx eax, al
    mov [ebp-84], eax
    mov eax, [ebp-84]
    cmp eax, 0
    je L4
    jmp L5
L4:
    mov eax, 0
    mov [ebp-80], eax
L5:
    mov eax, [ebp-80]
    cmp eax, 0
    je L6
    jmp L7
L6:
    mov eax, [ebp-12]
    mov ebx, 0
    cmp eax, ebx
    sete al
    movzx eax, al
    mov [ebp-32], eax
    mov eax, [ebp-32]
    cmp eax, 0
    setne al
    movzx eax, al
    xor eax, 1
    mov [ebp-36], eax
    mov eax, [ebp-36]
    cmp eax, 0
    je L6_f
    jmp L7
L6_f:
    mov eax, 0
    mov [ebp-28], eax
L7:
    mov eax, [ebp-28]
    cmp eax, 0
    je L2
    ; WRITE 111
    mov eax, 111
    push eax
    push fmt_write
    call printf
    add esp, 8
    jmp L3
L2:
    ; WRITE 222
    mov eax, 222
    push eax
    push fmt_write
    call printf
    add esp, 8
L3:
    mov eax, 0
    mov [ebp-20], eax
L8:
    mov eax, [ebp-20]
    mov ebx, 5
    cmp eax, ebx
    setl al
    movzx eax, al
    mov [ebp-40], eax
    mov eax, [ebp-40]
    cmp eax, 0
    je L10
    mov eax, [ebp-20]
    mov ebx, 1
    add eax, ebx
    mov [ebp-44], eax
    mov eax, [ebp-44]
    mov [ebp-20], eax
    jmp L8
L10:
    ; WRITE sum
    mov eax, [ebp-20]
    push eax
    push fmt_write
    call printf
    add esp, 8
    mov eax, 3
    mov [ebp-16], eax
L11:
    mov eax, [ebp-16]
    mov ebx, 0
    cmp eax, ebx
    setg al
    movzx eax, al
    mov [ebp-48], eax
    mov eax, [ebp-48]
    cmp eax, 0
    je L13
    ; WRITE i
    mov eax, [ebp-16]
    push eax
    push fmt_write
    call printf
    add esp, 8
    jmp L11
L13:
    mov eax, [ebp-20]
    mov ebx, 5
    cmp eax, ebx
    setne al
    movzx eax, al
    mov [ebp-52], eax
    mov eax, [ebp-52]
    cmp eax, 0
    je L15
    ; WRITE 333
    mov eax, 333
    push eax
    push fmt_write
    call printf
    add esp, 8
    jmp L16
L15:
    ; WRITE 444
    mov eax, 444
    push eax
    push fmt_write
    call printf
    add esp, 8
L16:
    mov eax, 0
    jmp main_ret
main_ret:
    mov esp, ebp
    pop ebp
    ret
