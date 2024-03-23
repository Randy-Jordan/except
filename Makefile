# Compiler Flags
CC := gcc
CFLAGS := -g -Wall -Wextra -Werror -pedantic -fsanitize=address,undefined -fno-omit-frame-pointer

# Directory variables 
LIBDIR := lib
OBJ := obj
INC := include
SRC := src
TEST := tests

# Filepath Pattern Matching
LIB := $(LIBDIR)/lib.a
SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
TESTS := $(wildcard $(TEST)/*.c)
TESTBINS := $(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

# Commands must be labeled PHONY
.PHONY: all release clean test

# Target for compilation.
all: $(LIB)

# Compiler Release Flags 
release: CFLAGS := -Wall -Wextra -Werror -pedantic -fsanitize=address,undefined -fno-omit-frame-pointer -O2 -DNDEBUG
release: clean $(LIB)

# Dependancies 
$(LIB): $(OBJS) | $(LIBDIR)
	$(RM) $(LIB)
	ar -cvrs $@ $^

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST)/bin/%: $(TEST)/%.c $(LIB) | $(TEST)/bin
	$(CC) $(CFLAGS) $< $(LIB) -o $@

# Make directories if none. 
$(LIBDIR):
	mkdir $@

$(INC):
	mkdir $@

$(OBJ):
	mkdir $@

$(TEST)/bin:
	mkdir $@

# Run the tests in the bin folder. Parent folder is working dir, not test | bin.
test: $(LIB) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS); do ./$$test ; done

clean:
	$(RM) -r $(LIBDIR) $(OBJ) $(TEST)/bin/
