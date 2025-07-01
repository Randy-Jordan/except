#include "../include/except.h"
#include <stdlib.h>
#include <stdio.h>

ExceptFrame *except_stack = NULL; // Global exception stack.
const Exception assert_failed = { "Assertion Failure!" }; // If ASSERT fails.

void except_raise(const Exception *e, const char *file,int line) {
    // An exception was raised, grab the exception stack.
	ExceptFrame *p = except_stack;
    asserted(e != NULL);  // Ensure exception pointer is not NULL
	if (p == NULL) { // Uncaught Exception
        const char *msg = e->reason ? e->reason : "Uncaught Exception!"; 
		fprintf(stderr,"\033[31m%s | Address: 0x%p | Raised at %s@%d \033[0m" ,msg,(void *)e,file,line);
        fflush(stderr);
        abort();
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
void asserted(int e) {
	ASSERTED(e);
    (void)e;
}
