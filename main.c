#include <stdio.h>
#include <windows.h>

int main(void) {

	printf("Better Serial\n");

	HANDLE hComm;
	hComm = CreateFile(
			"COM3",
			GENERIC_READ | GENERIC_WRITE,
			0, // exclusive access
			NULL, // no security attributes
			OPEN_EXISTING,
			0,
			NULL );

	if (hComm == INVALID_HANDLE_VALUE) {
		printf("Could not open the port.\n");
		return 0;
	} else {
		printf("Opened the port.\n");

		char buff[64];
		WORD nBytes;

		ReadFile(
			hComm,
			buff,
			7,
			&nBytes,
			NULL );


		printf("reading serial: %s\n", buff);

		CloseHandle(hComm);
		return 0;
	}


	return 0;
}
