#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

int establish_port(HANDLE *h_com_ptr) {

	*h_com_ptr = CreateFile(
			"COM3",
			GENERIC_READ | GENERIC_WRITE,
			0, // exclusive access
			NULL, // no security attributes
			OPEN_EXISTING,
			0,
			NULL );
}



int main(void) {

	printf("Better Serial\n");

	DCB dcb_params;
	dcb_params.DCBlength = sizeof(dcb_params);
	dcb_params.BaudRate = CBR_9600;
	dcb_params.ByteSize = 8;
	dcb_params.StopBits = ONESTOPBIT;
	dcb_params.Parity = NOPARITY;

	HANDLE hComm;

	establish_port( & hComm);

	if (hComm == INVALID_HANDLE_VALUE) {
		printf("Could not open the port.\n");
		return 0;
	}

	SetCommState(hComm, &dcb_params);

	printf("Opened the port.\n");

	char buff[64];
	DWORD nBytes;
	LPDWORD p_nBytes = &nBytes;

	char serial_buffer[64] = "hello\n";

	DWORD bytes_written;

	// later, right now, just use "hello\n"
	// scanf("%s", serial_buffer);

	bool status = WriteFile(hComm,
		serial_buffer,
		strlen(serial_buffer),
		&bytes_written,
		NULL );

	if ( ! status ) {
		printf("Something wrong happened...\n");
	}

	printf("bytes written: %d\n", bytes_written);

	bool read_status = ReadFile(
		hComm,
		buff,
		18,
		p_nBytes,
		NULL );

	if ( ! read_status) {
		printf("bad read\n");
	}

	buff[32] = '\0';

	printf("reading serial: %s\n", buff);

	CloseHandle(hComm);


	return 0;
}
