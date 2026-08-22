bits 64
; doing the syscalls for heap allocation
; awesomsauce

extern VirtualAlloc
extern GetStdHandle
extern WriteFile

global newAllocate
global WriteStdOut

section .text
newAllocate:
  sub rsp, 40 ; allocat phantom room for VirtualAlloc
  xor rcx, rcx
  mov rdx, 4096
  mov r8, 0x3000
  mov r9, 0x04

  call VirtualAlloc

  add rsp, 40 ; mane fuck the virtual room
  ret

bits 64
; WriteStdOut(const char *string, int length)

extern GetStdHandle
extern WriteFile
global WriteStdOut

section .text
WriteStdOut:
    push rbx
    push rsi
    mov rsi, rcx        ; save string  (rcx gets clobbered by GetStdHandle)
    mov ebx, edx        ; save length  (rdx gets clobbered by GetStdHandle)

    sub rsp, 40         ; 32 shadow space + 8 padding to keep 16-align at the call
    mov rcx, -11        ; STD_OUTPUT_HANDLE
    call GetStdHandle   ; -> rax = handle
    add rsp, 40

    sub rsp, 56         ; 32 shadow + 8 (lpOverlapped slot) + 8 (bytesWritten scratch) + 8 padding
    mov rcx, rax        ; hFile
    mov rdx, rsi        ; lpBuffer
    mov r8d, ebx        ; nNumberOfBytesToWrite
    lea r9, [rsp+40]    ; lpNumberOfBytesWritten -> scratch slot on our own stack
    mov qword [rsp+32], 0 ; lpOverlapped = NULL

    call WriteFile
    add rsp, 56

    pop rsi
    pop rbx
    ret
