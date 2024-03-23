#define DEBUG
#include "../include/logd.h"


int main(void){
    LOG_DEBUG(stdout,"Sanity Checks");
    TEST(NULL);
    TEST(0 > 1);
    TEST(1 > 0);
}
