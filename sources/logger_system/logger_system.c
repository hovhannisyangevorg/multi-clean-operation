#include "logger_system.h"

// Arrays for level names and colors
static const char* level_names[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL", "OFF"
};

static const char* level_colors[] = {
    "\033[34m",  // TRACE - Blue
    "\033[32m",  // DEBUG - Green
    "\033[37m",  // INFO - White
    "\033[33m",  // WARN - Yellow
    "\033[31m",  // ERROR - Red
    "\033[35m",  // FATAL - Magenta
    "\033[0m"    // RESET - Default
};

// Log message with level and color
void logger(t_level level, const char *message) {
    const char *level_name;
    const char *color;

    // Map log level to name and color
    switch (level) {
    case TRACE: level_name = level_names[0]; color = level_colors[0]; break;
    case DEBUG: level_name = level_names[1]; color = level_colors[1]; break;
    case INFO:  level_name = level_names[2]; color = level_colors[2]; break;
    case WARN:  level_name = level_names[3]; color = level_colors[3]; break;
    case ERROR: level_name = level_names[4]; color = level_colors[4]; break;
    case FATAL: level_name = level_names[5]; color = level_colors[5]; break;
    case OFF:   level_name = level_names[6]; color = level_colors[6]; break;
    default:    level_name = "UNKNOWN";      color = level_colors[6]; break;
    }

    printf("%s[%s] [%s] %s\033[0m\n", color, getCurrentTime(), level_name, message);
}

// Get current time as a string
const char* getCurrentTime() {
    static char time_buffer[20];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return time_buffer;
}
