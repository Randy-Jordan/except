#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
#include <setjmp.h>

struct Exception {
	const char *reason;
};
typedef struct Exception Exception;

struct ExceptFrame {
	ExceptFrame *prev;
	jmp_buf env;
	const char *file;
	int line;
	const Exception *exception;
};
typedef struct ExceptFrame ExceptFrame;

enum { EXCEPT_ENTERED, EXCEPT_RAISED, EXCEPT_HANDLED, EXCEPT_FINALIZED};
void hard_fail(const char* fmt, ...);


#endif
