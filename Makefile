CC      = gcc
CFLAGS  = -g `pkg-config --cflags gtk4`
RM      = rm -f
LIBS 	= `pkg-config --libs gtk4` 

OUT  	= out

MAIN_FILE 	= main.c
OUTP_LI  	= -o $(OUT)/main
OUTP_WIN 	= -o $(OUT)/main.exe


ifdef OS
	OUTP = $(OUTP_WIN)
else
	OUTP = $(OUTP_LI)
endif

default: make_main

all: make_li make_win

make_main: 
	$(CC) $(CFLAGS) $(OUTP) $(MAIN_FILE) $(LIBS)


make_li: $(MAIN_FILE)
	$(CC) $(CFLAGS) $(OUTP_LI) $(MAIN_FILE) $(LIBS)

make_win: $(MAIN_FILE)
	$(CC) $(CFLAGS) $(OUTP_WIN) $(MAIN_FILE) $(LIBS)

clean veryclean:
	$(RM) main.exe
	$(RM) main

$(shell   mkdir -p $(OUT))
