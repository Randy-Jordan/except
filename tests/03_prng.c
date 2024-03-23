#define DEBUG
#include "../include/logd.h"
#include <stdio.h>

int main(void){
    printf("\n");
    const int magic = 1804289383;
    LOG_DEBUG(stdout,"Testing prng functions, bad seed \"random int\" is %d",magic);
    BAD_PRNG();
    int bad_rand = rand();
    TEST(bad_rand == 1804289383);
    return EXIT_SUCCESS;
    
}
