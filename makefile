CC = gcc #/usr/local/bin/gcc-4.2
PREFIX = /usr/local
NDEBUG = -g
CFLAGS = -std=c99 -Wall -Werror -Wno-unused-variable -Wno-format-security -O3 -static $(NDEBUG) 
AS_SRCS = src/Assembler/*.c
OBJS = *.o
AS_PROG = cosivmas

ass:
	$(CC) $(CFLAGS) $(AS_SRCS) -o $(AS_PROG)
