# Use the gcc compiler.
CC = gcc
AR = ar

# Flags for the compiler.
CFLAGS = -Wall -Wextra -Werror -ggdb

# Command to remove files.
RM = rm -f

EXECUTABLES = digitcompress

.PHONY: all clean

all: $(EXECUTABLES)

digitcompress: encodemain.o compress.a
	$(CC) $(CFLAGS) -o digitcompress encodemain.o compress.a

encodemain.o: encodemain.c compress.h compress.o
	$(CC) $(CFLAGS) -c encodemain.c

compress.a: compress.o
	$(AR) -rcs compress.a compress.o

compress.o: compress.c compress.h
	$(CC) $(CFLAGS) -c compress.c

clean:
	$(RM) $(EXECUTABLES) *.o *.a