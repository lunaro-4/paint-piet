#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>

#define LOGFILE "log.log"

void logger(const char* message);

static FILE *logfile;



#endif /* LOG_H */
