CC = gcc
CFLAGS = -Iincludes -Wall -Wextra
# Iincludes: Tell the compiler to look for h files in "includes" (-I is the flag)
# Wall: Turn on standard warnings
# Wextra: Turn on additional warnings

# Add all C files
SRC = src/main.c src/parse.c src/tokenize.c

# Convert src/*.c file paths into output/*.o paths
OBJ = $(SRC:src/%.c=output/%.o)

# Path for final executable
EXEC = output/calculator

# Default target for "make" command
all: $(EXEC)

# How to build the final executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# How to compile .c files into .o files
output/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Run "make clean" to delete compiled files
clean:
	rm -f output/*.o $(EXEC)
