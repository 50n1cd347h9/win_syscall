#pragma once
#pragma comment (lib, "ntdll")

#include <Windows.h>
#include <stdio.h>

/*------[SETUP MACROS]------*/
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define warn(msg, ...) printf("[!] " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("[i] " msg "\n", ##__VA_ARGS__)

typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;                                                           //0x0
	VOID* RootDirectory;                                                    //0x8
	struct _UNICODE_STRING* ObjectName;                                     //0x10
	ULONG Attributes;                                                       //0x18
	VOID* SecurityDescriptor;                                               //0x20
	VOID* SecurityQualityOfService;                                         //0x28
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLnegth;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STIRNG;

typedef struct _CLIENT_ID {
	PVOID UniqueProcess;
	PVOID UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _PS_ATTRIBUTE {
	ULONGLONG Attribute;				
	SIZE_T Size;						
	union {
		ULONG_PTR Value;				
		PVOID ValuePtr;					
	};
	PSIZE_T ReturnLength;				
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST {
	SIZE_T TotalLength;					
	PS_ATTRIBUTE Attributes[2];			
} PS_ATTRIBUTE_LIST, *PPS_ATTRIBUTE_LIST;


extern NTSTATUS NtAllocateVirtualMemory(
		IN HANDLE ProcessHandle,
		IN OUT PVOID* BaseAddress,
		IN ULONG ZeroBits,
		IN OUT PSIZE_T RegionSize,
		IN ULONG AllocationType,
		IN ULONG Protect);

extern NTSTATUS NtOpenProcess(
		OUT PHANDLE ProcessHandle,
		IN ACCESS_MASK DesiredAccess,
		IN POBJECT_ATTRIBUTES ObjectAttributes,
		IN PCLIENT_ID ClientId OPTIONAL);

extern NTSTATUS NtCreateThreadEx(
		OUT PHANDLE ThreadHandle,
		IN ACCESS_MASK DesiredAccess,
		IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
		IN HANDLE ProcessHandle,
		IN PVOID StartRoutine,
		IN PVOID Argument OPTIONAL,
		IN ULONG CreateFlags,
		IN SIZE_T ZeroBits,
		IN SIZE_T StackSize,
		IN SIZE_T MaximumStackSize,
		IN PPS_ATTRIBUTE_LIST AttributeList OPTIONAL);

extern NTSTATUS NtWriteVirtualMemory(
		IN HANDLE ProcessHandle,
		IN PVOID BaseAddress,
		IN PVOID Buffer,
		IN SIZE_T NumberOfBytesToWrite,
		OUT PSIZE_T NumberOfBytesWritten OPTIONAL);

extern NTSTATUS NtWaitForSingleObject(
		_In_ HANDLE Handle,
		_In_ BOOLEAN Alertable,
		_In_opt_ PLARGE_INTEGER Timeout);

extern NTSTATUS NtClose(
		IN HANDLE Handle);
