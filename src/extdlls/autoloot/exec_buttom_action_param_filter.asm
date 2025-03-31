; It has to be done this way, because the calling convention used in this call uses XMM0-2 and then the normal calling convention of rcx, rdx, r9, etc.
; Problem is that, in a __vectorcall, the compiler wants to use XMM0-2, and then r9 and then it starts putting parameters on the stack. __fastcall does not
; seem to want to use XMM registers at all for a call, and everything gets misaligned. The result is that nothing has a prompt to use or pickup.

; Thank you tremwil(https://github.com/tremwil) for the suggestion and the help writing the asm wrapper. 

section .text
align 16

extern check_exec_action_button_param_filters
extern execute_action_button_param_proxy_return

global exec_action_button_param_proxy_hook

exec_action_button_param_proxy_hook:
    ; RCX = CSActionButtonRegionSystemImp*
    ; RDX = entryId
    push rcx
    push rdx
    push r8
    push r9
    sub rsp, 58h
    movaps [rsp+10h], xmm0
    movaps [rsp+20h], xmm1
    movaps [rsp+30h], xmm2

    call check_exec_action_button_param_filters
    movaps xmm0, [rsp-10h]
    movaps xmm1, [rsp-20h]
    movaps xmm2, [rsp-30h]
    add rsp, 58h
    pop r9
    pop r8
    pop rdx
    pop rcx
    cmp al, -1
    jz normal_flow
    ret

normal_flow:
    jmp [rel execute_action_button_param_proxy_return]
