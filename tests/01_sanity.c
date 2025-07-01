#define DEBUG
#include "../include/except.h"

#include <stdlib.h>
#include <stdio.h>

int main(void){
    printf("\n\n");
    printf("Assertion sanity test.\n");
    ASSERTED(NULL);
    return EXIT_SUCCESS;
    
}
