#define DEBUG
#include "../include/logd.h"
#include "../include/except.h"
#include <stdio.h>
#include <string.h>

int main(void){
    printf("\n\n");
    
    LOG_DEBUG(stdout,"Testing handling exceptions");
    Exception test_exception;
    TRY {
        TEST("In the try block.\n");
        LOG_DEBUG(stdout,"Simulating exception.");
        errno = 130;
        test_exception.reason = strerror(130);
        RAISE(test_exception);
    } EXCEPT(test_exception) {
        LOG_WARN(stderr,"ERRNO %d : %s",130,strerror(130));
        TEST(errno == 130);
        TEST("In the except block, handling exception.");
        errno = 0;
        TEST(errno != 130);
    }ELSE {
        LOG_ERROR(stderr,"An unexpected exception occured");
        TEST("In the else block.");
    } FINALLY {
        TEST("In the finally block, running cleanup\n");
    } END_TRY;
    TEST("Finished Try/Except block, exceptions handled.");
    TEST(errno == 0);
    TEST(except_stack == NULL);

    printf("\n\n");
    LOG_DEBUG(stdout,"Testing unexpected exceptions");
   TRY {
        TEST("In the try block again.\n");
        LOG_DEBUG(stdout,"Simulating exception, this time we don't expect it.");
        errno = 130;
        test_exception.reason = strerror(130);
        RAISE(test_exception);
    } EXCEPT(assert_failed) {
        LOG_WARN(stderr,"ERRNO %d : %s",130,strerror(130));
        TEST(errno == 130);
        TEST("In the except block, handling exception.");
        errno = 0;
        TEST(errno != 130);
    }ELSE {
        LOG_ERROR(stderr,"An unexpected exception occured");
        TEST("In the else block, this exception was unexpected.");
        errno = 0;
    } FINALLY {
        TEST("In the finally block, running cleanup\n");
    } END_TRY;
    TEST("Finished Try/Except block, exceptions handled.");
    TEST(errno == 0);
    TEST(except_stack == NULL);
 
    printf("\n\n");
    LOG_DEBUG(stdout,"Testing uncaught exceptions");
    RAISE(assert_failed);

    return EXIT_SUCCESS;
    
}
