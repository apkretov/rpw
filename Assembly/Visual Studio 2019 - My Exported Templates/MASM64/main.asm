EXTERN GetStdHandle : PROC
EXTERN WriteFile    : PROC
EXTERN ExitProcess  : PROC

.DATA?
    hFile           QWORD ?
    BytesWritten    DWORD ?

.DATA
    hello   BYTE 'Hello world!', 13, 10

.CODE
main PROC
    ; https://blogs.msdn.microsoft.com/oldnewthing/20160623-00/?p=93735
    sub rsp, 40                 ; Shadow space (4 * 8) & 1 parameter (8 bytes)
    ; https://docs.microsoft.com/en-us/cpp/build/stack-allocation
    and spl, -16                ; Align to 16

    ; https://msdn.microsoft.com/library/windows/desktop/ms683231.aspx
    mov ecx, -11                ; DWORD         nStdHandle = STD_OUTPUT_HANDLE
    call GetStdHandle           ; Call WinApi
    mov hFile, rax              ; Save returned handle

    ; https://msdn.microsoft.com/library/windows/desktop/aa365747.aspx
    mov rcx, hFile              ; HANDLE        hFile (here: Stdout)
    lea rdx, hello              ; LPCVOID       lpBuffer
    lea r9, BytesWritten        ; LPDWORD       lpNumberOfBytesWritten
    mov r8d, LENGTHOF hello     ; DWORD         nNumberOfBytesToWrite
    mov qword ptr [rsp+32], 0   ; LPOVERLAPPED  lpOverlapped = NULL
    call WriteFile              ; Call WinAPI

exit:
    ; https://msdn.microsoft.com/library/windows/desktop/ms682658.aspx
    xor ecx, ecx                ; Set RCX to null for return value
    call ExitProcess            ; Call WinAPI to exit
main ENDP

end