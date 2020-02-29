#include <stdio.h>
#include <windows.h>

int main(void) {

	printf("Better Serial\n");

	DCB dcb_params;
	dcb_params.DCBlength = sizeof(dcb_params);
	dcb_params.BaudRate = CBR_9600;
	dcb_params.ByteSize = 8;
	dcb_params.StopBits = ONESTOPBIT;
	dcb_params.Parity = NOPARITY;


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
	}

	SetCommState(hComm, &dcb_params);

	printf("Opened the port.\n");

	char buff[64];
	DWORD nBytes;
	LPDWORD p_nBytes = &nBytes;

	ReadFile(
		hComm,
		buff,
		7,
		p_nBytes,
		NULL );


		printf("reading serial: %s\n", buff);

		CloseHandle(hComm);
		return 0;


	return 0;
}
