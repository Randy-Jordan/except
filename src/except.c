#include "../include/except.h"
#include <string.h>
#include <stdarg.h>
ExceptFrame *except_stack = NULL;
const Exception assert_failed = { "Assertion failed" };

void hard_fail(const char *fmt, ...){
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
	ExceptFrame *p = except_stack;
	//assert(e);
	if (p == NULL) {
        char *msg = NULL;
        if(!e->reason) msg = "NULL MSG";
        msg = (char *)e->reason;
		hard_fail("Uncaught exception: %s | Address: 0x%p | raised at %s@%d\n",msg,(void *)e,file,line);
    }
	p->exception = e;
	p->file = file;
	p->line = line;
	except_stack = except_stack->prev;
	longjmp(p->env, EXCEPT_RAISED);
}

void (assert)(int e) {
	ASSERT(e);
}
