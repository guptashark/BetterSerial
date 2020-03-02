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

	return 0;
}

int config_port(DCB * dcb_params_ptr) {

	dcb_params_ptr->BaudRate = CBR_9600;
	dcb_params_ptr->ByteSize = 8;
	dcb_params_ptr->StopBits = ONESTOPBIT;
	dcb_params_ptr->Parity = NOPARITY;

	return 0;
}


int main(void) {

	printf("Better Serial\n");

	DCB dcb_params;

	// not setting by pointer rn.
	dcb_params.DCBlength = sizeof(dcb_params);

	HANDLE hComm;

	establish_port( & hComm);
	config_port( & dcb_params);

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

	buff[18] = '\0';

	printf("reading serial: %s\n", buff);

	CloseHandle(hComm);


	return 0;
}
