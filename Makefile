#
# Makefile for TinyNoise
#
# Author: Cesar Pires Severo
# Since: 02.16.2025
#

# Built artifacts names
LIB = tiny_noise
BINARY = $(LIB)


# Gets the Operating system name
OS := $(shell uname -s)

# Default shell
SHELL := bash

# Color prefix for Linux distributions
COLOR_PREFIX := e

# Source code directory structure
BINDIR := build
SRCDIR := src
LIBDIR := lib
TESTDIR := test

# Source code file extension
SRCEXT := c

# Defines the C Compiler
CC := gcc

# Defines the language standards for GCC
STD := -std=gnu99  

# Protection for stack-smashing attack
STACK := -fstack-protector-all -Wstack-protector

# Specifies to GCC the required warnings
WARNS := -Wall -Wextra -pedantic 

# Flags for compiling
CFLAGS := -O3 $(STD) $(STACK) $(WARNS)

# Debug options
DEBUG := -g3 -DDEBUG=1

# Test libraries
TEST_LIBS := -l cmocka -L /usr/lib

# Test source file name
TEST_SRC := test_$(BINARY)

# Tests binary file
TEST_BINARY := $(BINARY)_test_runner

# %.o file names
NAMES := $(notdir $(basename $(wildcard $(SRCDIR)/*.$(SRCEXT))))
OBJECTS :=$(patsubst %,$(LIBDIR)/%.o,$(NAMES))


#
# COMPILATION RULES
#

default: lib

# Help message
help:
	@echo "----- TinyNoise -----"
	@echo
	@echo "- Target rules:"
	@echo "    lib      - Compiles and generates a library file"
	@echo "    tests    - Compiles with cmocka and run tests binary file"
	@echo "    clean    - Clean the project by removing binaries"
	@echo "    help     - Prints a help message with target rules"


# Rule for generating the library file
lib: $(OBJECTS)
	@echo "Building the library..."
	$(CC) -o $(BINDIR)/$(BINARY) $+ $(DEBUG) $(CFLAGS)


# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) -c $^ -o $@ $(DEBUG) $(CFLAGS)


# Compile tests and run the test binary
tests:
	$(CC) $(TESTDIR)/$(TEST_SRC) -o $(BINDIR)/$(TEST_BINARY) $(DEBUG) $(CFLAGS) $(TEST_LIBS)
	@which ldconfig && ldconfig -C /tmp/ld.so.cache || true 
	@echo  "Running tests..."
	./$(BINDIR)/$(TEST_BINARY)


# Rule for cleaning the project
clean:
	@rm -rvf $(BINDIR)/* $(LIBDIR)/*;
