section .text
align 16

extern ml_properties_on_init
extern ml_property_init_trampoline

global ml_property_init_hook_raw

ml_property_init_hook_raw:
    lea rsp, [rsp-80h]
    pushfq
    push rax
    mov rax, rsp
    and rsp, -16
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11
    sub rsp, 68h
    movdqu [rsp+00h], xmm0
    movdqu [rsp+10h], xmm1
    movdqu [rsp+20h], xmm2
    movdqu [rsp+30h], xmm3
    movdqu [rsp+40h], xmm4
    movdqu [rsp+50h], xmm5
    sub rsp, 20h
    call ml_properties_on_init
    add rsp, 20h
    movdqu xmm0, [rsp+00h]
    movdqu xmm1, [rsp+10h]
    movdqu xmm2, [rsp+20h]
    movdqu xmm3, [rsp+30h]
    movdqu xmm4, [rsp+40h]
    movdqu xmm5, [rsp+50h]
    add rsp, 68h
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rsp
    pop rax
    popfq
    lea rsp, [rsp+80h]
    jmp [rel ml_property_init_trampoline]
