#include "../include/logd.h"

static const char *level_colors[] = {
  ANSI_COLOR_BLUE, ANSI_COLOR_MAGENTA, ANSI_COLOR_GREEN, ANSI_COLOR_YELLOW, BOLD_RED, ANSI_COLOR_RED
};
static const char *level_strings[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};
void logd( FILE *stream, int level, const char *file, int line, const char *format, ...) {
    UNUSED(file);
    UNUSED(line);
    // Ensure the level is within the valid range
    if (level >= LEVEL_TRACE && level <= LEVEL_FATAL) {
        fprintf(stream,"%s %s ",__DATE__,__TIME__);
        
        fprintf(stream,"[%s@%d] ",__FILE__,__LINE__);  
        fprintf(stream,"%s[%s] "CRESET,level_colors[level], level_strings[level]);
        va_list args;
        va_start(args, format);
        vfprintf(stream,format,args);
        fprintf(stream,"\n");
        va_end(args);
    } else {
        return;
    }

}
