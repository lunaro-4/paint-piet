CC      = gcc
CFLAGS  = -g `pkg-config --cflags gtk4`
RM      = rm -f
LIBS 	= `pkg-config --libs gtk4 --libs spng --libs libpng` 

OUT  	= out

INPUT_FILES 	= main.c colormatrix.c custom_utils.c
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
	$(CC) $(CFLAGS) $(OUTP) $(INPUT_FILES) $(LIBS)


make_li: $(INPUT_FILES)
	$(CC) $(CFLAGS) $(OUTP_LI) $(INPUT_FILES) $(LIBS)

make_win: $(INPUT_FILES)
	$(CC) $(CFLAGS) $(OUTP_WIN) $(INPUT_FILES) $(LIBS)

clean veryclean:
	$(RM) main.exe
	$(RM) main

$(shell   mkdir -p $(OUT))
