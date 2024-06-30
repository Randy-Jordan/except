#include "../include/except.h"
#include <string.h>
#include <stdarg.h>

ExceptFrame *except_stack = NULL; // Global exception stack.
const Exception assert_failed = { "Assertion failed" }; // If ASSERT fails.

void hard_fail(const char *fmt, ...){ // Error msg and exit.
    int errno_save;
    va_list ap;
    // Any syscall or library can change errno, need to save it.
    errno_save = errno;

    // Print out error fmt+args to stderr
    va_start(ap,fmt);
    vfprintf(stderr,fmt,ap);
    fprintf(stderr,"\n");
    fflush(stderr);

    // Print out errno if it was set 
    if(errno_save != 0){
        fprintf(stderr,"ERRNO %d : %s\n",errno_save,strerror(errno_save));
        fflush(stderr);
    }
    va_end(ap);
    exit(EXIT_FAILURE);
}
void except_raise(const Exception *e, const char *file,int line) {
    // An exception was raised, grab the exception stack.
	ExceptFrame *p = except_stack;
    assert(e != NULL);  // Ensure exception pointer is not NULL
	if (p == NULL) { // Uncaught Exception
        const char *msg = e->reason ? e->reason : "Uncaught Exception"; 
		hard_fail("%s | Address: 0x%p | raised at %s@%d\n",msg,(void *)e,file,line);
    }
   // Set the exception details to the current frame. 
	p->exception = e; // Exception reason
	p->file = file;
	p->line = line;
    // Move to the previous frame in the stack.
	except_stack = except_stack->prev;
    // Jump to the saved context environment.
	longjmp(p->env, EXCEPT_RAISED);
}
void (assert)(int e) {
	ASSERT(e);
}
