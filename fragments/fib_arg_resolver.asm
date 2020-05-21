BITS 64

; rdi -> target
; rsi -> arg_list
; rdx -> arg_list_len
; rcx -> retval_ptr

mov r11, rdi ; vacate rdi
mov rdi, [rsi] ; get value pointer
mov rdi, [rdi] ; dereference value pointer
push rsi
push rcx
call r11
pop rcx
pop rsi

mov [rcx], rax