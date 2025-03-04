.386
.model flat, stdcall
.stack 4096
ExitProcess proto, dwExitCode: DWORD

.data
	; define your variables here
.code

main proc
	; write your assembly code here
	
	INVOKE ExitProcess, 0
main ENDP
END main