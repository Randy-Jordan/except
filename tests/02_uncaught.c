#define DEBUG
#include "../include/except.h"

#include <stdlib.h>
#include <stdio.h>

int main(void){
    printf("\n\n");
    printf("Uncaught exceptions sanity test.\n");
    Exception u = {NULL};
    RAISE(u);
    return EXIT_SUCCESS;
    
}
