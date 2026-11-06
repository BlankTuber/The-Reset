CC = gcc
CFLAGS = -Iincludes -Wall -Wextra
# Iincludes: Tell the compiler to look for h files in "includes" (-I is the flag)
# Wall: Turn on standard warnings
# Wextra: Turn on additional warnings

# Everything except main.c (shared by the program and the tests)
LIB_SRC = src/parse.c src/tokenize.c

# Add all C files
SRC = src/main.c $(LIB_SRC)

# Convert src/*.c file paths into output/*.o paths
OBJ = $(SRC:src/%.c=output/%.o)

# Path for final executable
EXEC = output/calculator

# Test files and executable
TEST_SRC = tests/test_tokenize.c
TEST_EXEC = output/run_tests

# Default target for "make" command
all: $(EXEC)

# How to build the final executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# How to compile .c files into .o files
output/%.o: src/%.c
	@mkdir -p output
	$(CC) $(CFLAGS) -c $< -o $@

# Build (if needed) and run the calculator
run: $(EXEC)
	./$(EXEC)

# Build and run tests (main.c is left out, since the test file has its own main)
test: $(TEST_SRC) $(LIB_SRC)
	@mkdir -p output
	$(CC) $(CFLAGS) -g -fsanitize=address,undefined $(TEST_SRC) $(LIB_SRC) -o $(TEST_EXEC)
	./$(TEST_EXEC)

# Run "make clean" to delete compiled files
clean:
	rm -f output/*.o $(EXEC) $(TEST_EXEC)

.PHONY: all test clean
