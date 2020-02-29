CC = cl
CFLAGS = /nologo

SRC = main.c

all:
	$(CC) $(CFLAGS) $(SRC)
	main.exe
