section .text
	global NtClose
	global NtOpenProcess

NtOpenProcess:
	mov r10, rcx
	mov eax, 0x26
	syscall
	ret

NtAllocateVirtualMemory:
	mov r10, rcx
	mov eax, 0x18
	syscall
	ret

NtWriteVirtualMemory:
	mov r10, rcx
	mov eax, 0x3a
	syscall
	ret

NtCreateThreadEx:
	mov r10, rcx
	mov eax, 0xc2
	syscall
	ret

NtWaitForSingleObject:
	mov r10, rcx
	mov eax, 0x4
	syscall
	ret

NtClose:
	mov r10, rcx
	mov eax, 0xf
	syscall
	ret
