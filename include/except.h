#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <setjmp.h>
#include <errno.h>

struct Exception {
	const char *reason;
};
typedef struct Exception Exception;

struct ExceptFrame {
	struct ExceptFrame *prev;
	jmp_buf env;
	const char *file;
	int line;
	const Exception *exception;
};
typedef struct ExceptFrame ExceptFrame;

enum { EXCEPT_ENTERED=0, EXCEPT_RAISED, EXCEPT_HANDLED, EXCEPT_FINALIZED};
void except_raise(const Exception *e, const char *file,int line);
void hard_fail(const char* fmt, ...);

extern ExceptFrame *except_stack; // Global exception stack
extern const Exception assert_failed;

#undef ASSERT
#ifdef NDEBUG
#define ASSERT(e) ((void)0)
#else
extern void assert(int e);
#define ASSERT(e) ((void)((e)||(RAISE(assert_failed),0)))
#endif

#define RAISE(e) except_raise(&(e), __FILE__, __LINE__)
#define RERAISE except_raise(except_frame.exception, \
	except_frame.file, except_frame.line)
#define RETURN switch (except_stack = except_stack->prev,0) default: return
#define TRY do { \
	volatile int except_flag; \
	ExceptFrame except_frame; \
	except_frame.prev = except_stack; \
	except_stack = &except_frame;  \
	except_flag = setjmp(except_frame.env); \
	if (except_flag == EXCEPT_ENTERED) {
#define EXCEPT(e) \
		if (except_flag == EXCEPT_ENTERED) except_stack = except_stack->prev; \
	} else if (except_frame.exception == &(e)) { \
		except_flag = EXCEPT_HANDLED;
#define ELSE \
		if (except_flag == EXCEPT_ENTERED) except_stack = except_stack->prev; \
	} else { \
		except_flag = EXCEPT_HANDLED;
#define FINALLY \
		if (except_flag == EXCEPT_ENTERED) except_stack = except_stack->prev; \
	} { \
		if (except_flag == EXCEPT_ENTERED) \
			except_flag = EXCEPT_FINALIZED;
#define END_TRY \
		if (except_flag == EXCEPT_ENTERED) except_stack = except_stack->prev; \
		} if (except_flag == EXCEPT_RAISED) RERAISE; \
} while (0)

#endif
