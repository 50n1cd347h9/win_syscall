#include <windows.h>
#include "./useful.h"


int main(int argc, char* argv[]) {
	DWORD PID = NULL;
	HANDLE hProcess = NULL;
	NTSTATUS STATUS = NULL;

	if (argc < 2) {
		warn("usage: %s <PID>", argv[0]);
		return EXIT_FAILURE;
	}

	PID = atoi(argv[1]);
	OBJECT_ATTRIBUTES OA = { sizeof(OA), NULL };
	CLIENT_ID CID = { (HANDLE)PID, NULL};

	info("getting a handle on process (%ld)...", PID);
	STATUS = NtOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &OA, &CID);

	if (STATUS != STATUS_SUCCESS) {
		warn("[NtOpenProcess], error: 0x%lx", STATUS);
		return EXIT_FAILURE;
	}
	okay("got a handle on the process!");
	info("\\___[ hProcess\n\t\\_0x%p]", hProcess);

	info("closing handle on process (%ld)...", PID);
	STATUS = NtClose(hProcess);

	if (STATUS != STATUS_SUCCESS) {
		warn("[NtClose], error: 0x%lx", STATUS);
		return EXIT_FAILURE;
	}
	okay("closed a handle on the process!");

	return EXIT_SUCCESS;
}
