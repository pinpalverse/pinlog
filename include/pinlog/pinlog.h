#ifndef __PIN_LOG
#define __PIN_LOG

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TIME_FMT "%H:%M:%S" // you can change it to what suits you
#define TIME_FMT_SIZE                                                          \
  4 + 1 + 2 + 1 + 2 // if TIME_FMT changes, this should also change or else
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
                               const char *fmt, ...);

#define pinlog_to_file(lvl, out_file, fmt, ...)\
{\
    _vinternal_pinlog_to_file(lvl, out_file, __LINE__, __FILE_NAME__, __func__,\
                             fmt, ##__VA_ARGS__);}


#define pinlog(lvl, fmt, ...)\
{\
    _vinternal_pinlog_to_file(lvl, stdout, __LINE__, __FILE_NAME__, __func__,\
                             fmt, ##__VA_ARGS__);}


#endif
