CC      = gcc
CFLAGS  = -g `sdl2-config --cflags` -I ./sdl2dev/include/SDL2
RM      = rm -f
LIBS 	= -lSDL2  -L ./sdl2dev/lib
MAINFILE = main.c


ifdef OS
	OUTP = -o test.exe
else
	OUTP = -o test
endif

default: make_main

all: make_li make_win

make_main: 
	$(CC) $(CFLAGS) $(OUTP) test.c $(LIBS)


make_li: main.c
	$(CC) $(CFLAGS) -o main main.c $(LIBS)

make_win: main.c
	$(CC) $(CFLAGS) -o main.exe main.c $(LIBS)

clean veryclean:
	$(RM) main.exe
	$(RM) main


