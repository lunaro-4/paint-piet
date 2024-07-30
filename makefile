CC      = gcc
CFLAGS  = -g
RM      = rm -f


ifdef OS
	OUTP = -o main.exe
else
	OUTP = -o main
endif

default: make_main

all: make_li make_win

make_main: 
	$(CC) $(CFLAGS) $(OUTP) main.c


make_li: main.c
	$(CC) $(CFLAGS) -o main main.c

make_win: main.c
	$(CC) $(CFLAGS) -o main.exe main.c

clean veryclean:
	$(RM) main.exe
	$(RM) main


