#define DEBUG
#include "../include/except.h"
#include <stdio.h>
#include <string.h>

int main(void){
    printf("\n\n");
    
    printf("Testing handling exceptions \n");
    Exception test_exception;
    TRY {
        TEST("In the try block.\n");
        printf("Simulating exception.\n");
        errno = 130;
        test_exception.reason = strerror(130);
        RAISE(test_exception);
    } EXCEPT(test_exception) {
        printf("ERRNO %d : %s\n",130,strerror(130));
        TEST(errno == 130);
        TEST("In the except block, handling exception.");
        errno = 0;
        TEST(errno != 130);
    }ELSE {
        printf("An unexpected exception occured\n");
        TEST("In the else block.");
    } FINALLY {
        TEST("In the finally block, running cleanup");
    } END_TRY;
    TEST("Finished Try/Except block, exceptions handled.");
    TEST(errno == 0);
    TEST(except_stack == NULL);

    printf("\n\n");
    printf("Testing unexpected exceptions\n");
   TRY {
        TEST("In the try block again.");
        printf("Simulating exception, this time we don't expect it.\n");
        errno = 130;
        test_exception.reason = strerror(130);
        RAISE(test_exception);
    } EXCEPT(assert_failed) {
        printf("ERRNO %d : %s\n",130,strerror(130));
        TEST(errno == 130);
        TEST("In the except block, handling exception.");
        errno = 0;
        TEST(errno != 130);
    }ELSE {
        printf("An unexpected exception occured\n");
        TEST("In the else block, this exception was unexpected.");
        errno = 0;
    } FINALLY {
        TEST("In the finally block, running cleanup");
    } END_TRY;
    TEST("Finished Try/Except block, exceptions handled.");
    TEST(errno == 0);
    TEST(except_stack == NULL);
 
    printf("\n\n");
    printf("Testing uncaught exceptions\n");
    Exception u = {NULL};
    RAISE(u);

    return EXIT_SUCCESS;
    
}
