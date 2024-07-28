#define DEBUG
#include "../include/except.h"
#include <stddef.h>

int main(void){
    TEST(NULL);
    TEST(0 > 1);
    TEST(1 > 0);
}
