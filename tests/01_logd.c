#define DEBUG

#include "../include/logd.h"
#include <stdlib.h>


int main(void){
    printf("\n\n");
    const char *str = "Hello";
    int num = 7;
    LOG_TRACE(stdout,"Testing log trace.");
    LOG_DEBUG(stdout,"Testing log debug with str %s and int %d", str,num);
    LOG_INFO(stdout,"Testing log info");
    LOG_WARN(stdout,"Testing log warning");
    LOG_ERROR(stdout,"Testing log error");
    LOG_FATAL(stdout,"Testing log fatal");
    printf("\n");
    return EXIT_SUCCESS;
}
