#include "../include/except.h"
ExceptFrame *except_stack = NULL;
void Except_raise(const Exception *e, const char *file,int line) {
	ExceptFrame *p = except_stack;
	//assert(e);
	if (p == NULL) {
		fprintf(stderr, "Uncaught exception");
		if (e->reason)
			fprintf(stderr, " %s", e->reason);
		else
			fprintf(stderr, " at 0x%p", (void *)e);
		if (file && line > 0)
			fprintf(stderr, " raised at %s:%d\n", file, line);
		fprintf(stderr, "aborting...\n");
		fflush(stderr);
		abort();
	}
	p->exception = e;
	p->file = file;
	p->line = line;
	except_stack = except_stack->prev;
	longjmp(p->env, EXCEPT_RAISED);
}
void hard_fail(const char *fmt, ...);
