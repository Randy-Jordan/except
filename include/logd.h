#ifndef LOGD_INCLUDED
#define LOGD_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define NOW     time(NULL)
#define SEED_PRNG() srand(time(NULL) ^ getpid())
#define BAD_PRNG() srand(1)

// ANSI color escape codes
#define CRESET   "\x1b[0m"
#define ANSI_COLOR_BLACK "\e[0;30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define BOLD_RED "\x1b[1;91m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"

// ANSI style escape codes
#define ANSI_STYLE_BOLD      "\x1b[1m"
#define ANSI_STYLE_UNDERLINE "\x1b[4m"

enum {LEVEL_TRACE=0,LEVEL_DEBUG,LEVEL_INFO,LEVEL_WARN,LEVEL_ERROR,LEVEL_FATAL,LEVEL_COUNT};

#define LOG_TRACE(stream, ...) logd(stream,LEVEL_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(stream, ...) logd(stream,LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(stream, ...)  logd(stream,LEVEL_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(stream, ...)  logd(stream,LEVEL_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(stream, ...) logd(stream,LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(stream, ...) logd(stream,LEVEL_FATAL, __FILE__, __LINE__, __VA_ARGS__)
void logd(FILE *stream, int level, const char *file, int line, const char *fmt, ...);

#ifdef DEBUG
#define TEST_FAILED(expr) printf(__DATE__" " __TIME__ " [%s@%d] " ANSI_COLOR_RED "FAILED %s \n"CRESET, __FILE__, __LINE__, #expr)
#define TEST_PASSED(expr) printf(__DATE__" " __TIME__ " [%s@%d] " ANSI_COLOR_GREEN "PASSED %s\n"CRESET, __FILE__, __LINE__, #expr)
#define TEST(expr) ((expr) ? TEST_PASSED(expr) : TEST_FAILED(expr))
#else
#define TEST_FAILED(expr)
#define TEST_PASSED(expr)
#define TEST(expr)
#endif

#endif
