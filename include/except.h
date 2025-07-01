#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED

#include <setjmp.h>

struct Exception {
	const char *reason;
};
typedef struct Exception Exception;

struct ExceptFrame {
	struct ExceptFrame *prev;   // Exception Stack
	jmp_buf env;                // Enviroment Buffer
    	const char *file;           // Exception File
	int line;                   // Exception Line
	const Exception *exception; // Exception Reason
};
typedef struct ExceptFrame ExceptFrame;

// Exception States 
enum { EXCEPT_ENTERED=0, EXCEPT_RAISED, EXCEPT_HANDLED, EXCEPT_FINALIZED};

void except_raise(const Exception *e, const char *file,int line); // Raise exceptions

// External declarations 
extern ExceptFrame *except_stack; // Global exception stack
extern const Exception assert_failed; // Forward declaration for assert. 
extern void asserted(int e);

#ifdef NDEBUG
#define ASSERTED(e) ((void)0)
#else
#define ASSERTED(e) ((void)((e)||(RAISE(assert_failed),0)))
#endif

// Raise an Exception.
#define RAISE(e) except_raise(&(e), __FILE__, __LINE__)

// Reraise the currect exception.
#define RERAISE except_raise(except_frame.exception, \
	except_frame.file, except_frame.line)

// Switch to the previous exception frame and return.
#define RETURN switch (except_stack = except_stack->prev,0) default: return

// Start a try block.
#define TRY do { \
	volatile int except_flag; \
	ExceptFrame except_frame; \
	except_frame.prev = except_stack; \
	except_stack = &except_frame;  \
	except_flag = setjmp(except_frame.env); \
	if (except_flag == EXCEPT_ENTERED) {

// Handle specific example.
#define EXCEPT(e) \
		if (except_flag == EXCEPT_ENTERED) except_stack = except_stack->prev; \
	} else if (except_frame.exception == &(e)) { \
		except_flag = EXCEPT_HANDLED;

// Catch all other exceptions.        
#define ELSE \
		if (except_flag == EXCEPT_ENTERED) except_stack = except_stack->prev; \
	} else { \
		except_flag = EXCEPT_HANDLED;

// Execute finalization code.        
#define FINALLY \
		if (except_flag == EXCEPT_ENTERED) except_stack = except_stack->prev; \
	} { \
		if (except_flag == EXCEPT_ENTERED) \
			except_flag = EXCEPT_FINALIZED;

// End Try block.         
#define END_TRY \
		if (except_flag == EXCEPT_ENTERED) except_stack = except_stack->prev; \
		} if (except_flag == EXCEPT_RAISED) RERAISE; \
} while (0)

#endif
