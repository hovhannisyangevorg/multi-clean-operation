#ifndef LOGGER_SYSTEM_H
#define LOGGER_SYSTEM_H

#include <stdio.h>
#include <string.h>
#include <time.h>

typedef enum s_level t_level;

// Log levels
enum s_level {
    TRACE = 1 << 0,
    DEBUG = 1 << 1,
    INFO  = 1 << 2,
    WARN  = 1 << 3,
    ERROR = 1 << 4,
    FATAL = 1 << 5,
    RESET = 1 << 6,
    OFF   = 1 << 6
};

void logger(t_level level, const char *message);
const char* getCurrentTime();

#endif //LOGER_HPP



