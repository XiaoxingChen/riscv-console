.section .init, "ax"
.global _start
_start:
    .cfi_startproc
    .cfi_undefined ra
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, __stack_top
    add s0, sp, zero
    jal ra, init
    nop
    jal zero, main
    .cfi_endproc
    

.section .text, "ax"
.global getTicks, getStatus, hookFunction
getTicks:
    li a5, 0
    ecall
getStatus:
    li a5, 1
    ecall
; writeTargetMem:
;     li a5, 6
;     ecall
; writeTarget:
;     li a5, 7
;     ecall
hookFunction:
    li a5, 8
    ecall
.end