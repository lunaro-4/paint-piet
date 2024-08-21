#include "logger.h"
#include <stdio.h>
#include <time.h>



void logger(const char* message) {
	logfile = fopen(LOGFILE, "a");
	// long length = (sizeof message / sizeof message[0]);
	time_t now;
	time(&now);
	char to_write[10000];
	sprintf(to_write, "%s: %s", ctime(&now), message);
	printf("%s\n", to_write);
	// fwrite(to_write, sizeof(char), length, logfile);
	// fwrite("amogus", sizeof(char), 6, logfile);
	fprintf(logfile, "%s\n", to_write);
	fclose(logfile);
}
