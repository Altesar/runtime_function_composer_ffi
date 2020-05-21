BITS 64

%define MEDIUM_REG 0
%define MEDIUM_MMX 1

push    r12
push    r13
push    r14
push    r15

mov     r11, [rbp - (4*8)]  ; argument list struct ptr
mov     r12, [r11]          ; num arguments
mov     r13, [r11 + 8]      ; arg_list
mov     r14, 0              ; reg_arg_counter
mov     r15, 0              ; mmx_arg_counter
mov     r9,  0              ; totoal_arg_count

reg_loop:
    mov     r11, [r13 + 8*r14]  ; arg_list[i]
    mov     r15, [r11 + 8]      ; arg_type

    cmp     r15, MEDIUM_REG
    jz      set_arg_reg
    jnz     set_arg_mmx

    cmp     r9, r13
    inc     r9
    jz      reg_loop_done
    jmp     reg_loop

    set_arg_reg:
        ; TODO: turn into macro
        cmp     r14, 0
        jnz     __set_arg_reg_1
            push    r15
            mov     r15, [r11]
            mov     rsi, [r15]
            pop     r15
            jmp     set_arg_reg_done
        __set_arg_reg_1:



    set_arg_reg_done:
        jmp     reg_loop

    set_arg_mmx:

    set_arg_mmx_done:
        jmp     reg_loop

reg_loop_done:

pop r15
pop r14
pop r13
pop r12