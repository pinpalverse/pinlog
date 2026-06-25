#include "../include/pinlog.h"


void _vinternal_pinlog_to_file(LOG_LEVEL lvl, FILE *out_file, int line,
                               const char *file, const char *func,
                               const char *fmt, ...)
{
    char *time_buffer = (char *)malloc(TIME_FMT_SIZE * sizeof(char));
    time_t timer = time(NULL);
    struct tm *tm_info;
    tm_info = localtime(&timer);
    strftime(time_buffer, TIME_FMT_SIZE, TIME_FMT, tm_info);
    printf("%s %s[%s] %s:%d %s()%s > ", time_buffer,
           lvl == DEBUG ? COLOR_MAGENTA :
           lvl == LOG ? COLOR_WHITE :
           lvl == ERROR ? COLOR_RED :
           lvl == WARN ? COLOR_YELLOW :
           lvl == INFO ? COLOR_BLUE :
           lvl == SUCCESS ? COLOR_GREEN : COLOR_WHITE,
           lvl == DEBUG ? "DEBUG" :
           lvl == LOG ? "LOG" :
           lvl == ERROR ? "ERROR" :
           lvl == WARN ? "WARN" :
           lvl == INFO ? "INFO" :
           lvl == SUCCESS ? "SUCCESS" : "N/A",
           file, line, func, COLOR_RESET);
    va_list argptr;
    va_start(argptr, fmt);
    vfprintf(out_file, fmt, argptr);
    va_end(argptr);
    printf("\n");
    fflush(out_file);
    free(time_buffer);
}

