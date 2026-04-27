#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIME_FMT "%H:%M:%S\0" // you can change it to what suits you
#define TIME_FMT_SIZE                                                          \
  4 + 1 + 2 + 1 + 2 + 1 // if TIME_FMT changes, this should also change or else
// u might get a buffer overflow
typedef enum { DEBUG, LOG, ERROR, WARN, INFO, SUCCESS } LOG_LEVEL;

#define COLOR_RESET   "\033[0m"
#define COLOR_BLACK   "\033[30m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_WHITE   "\033[37m"

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

#define pinlog_to_file(lvl, out_file, fmt, ...)\
{\
    _vinternal_pinlog_to_file(lvl, out_file, __LINE__, __FILE_NAME__, __func__,\
                             fmt, ##__VA_ARGS__);}


#define pinlog(lvl, fmt, ...)\
{\
    _vinternal_pinlog_to_file(lvl, stdout, __LINE__, __FILE_NAME__, __func__,\
                             fmt, ##__VA_ARGS__);}
