#
# Makefile for TinyNoise
#
# Author: Cesar Pires Severo
# Since: 02.16.2025
#

# Directories used in the project
BINDIR := build
SRCDIR := src
LIBDIR := lib
TESTDIR := test

# Name of the test source file
TESTSRC := main

# Test executable name
TESTEXE := tn_test_runner

# Source files
CFILES := $(notdir $(basename $(wildcard $(SRCDIR)/*.c)))

# Object files
OFILES := $(patsubst %,$(LIBDIR)/%.o,$(CFILES))

# Compiler definition
CC := gcc

# Compiler flags
CFLAGS = -O2 -Wall -Wextra -Werror

# Include flags
IFLAGS = -I$(SRCDIR)

# Library name
LIBNAME = tinynoise

# Library linking flags
LDFLAGS= -L$(BINDIR) -l$(LIBNAME) -lm 

#
# Compilation Rules
#

$(info ----- TinyNoise -----)

default: help

# Help message 
help:
	@echo "- Target rules:"
	@echo "    all      - Compiles the static library"
	@echo "    tests    - Compiles with cmocka and run tests binary file"
	@echo "    clean    - Removes all build artifacts from lib and build folders"
	@echo "    help     - Prints a help message with target rules (Default)"

# Rule for building objects and static library
all: $(LIBNAME).a
	$(info Done!)

# Rule for static library build
$(LIBNAME).a: $(OFILES)
	$(info Building the library...)
	@ar rcs $(BINDIR)/$(LIBNAME).a $(OFILES) 

# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.c
	$(info Compiling source files...)
	@$(CC) -c $^ -o $@ $(CFLAGS)

# Rule for test executable build
tests: $(LIBNAME).a $(BINDIR)/$(TESTEXE)
	$(info Done!)
	
$(BINDIR)/$(TESTEXE): $(LIBDIR)/$(TESTSRC).o
	$(info Building test executable...)
	@$(CC) -o $(BINDIR)/$(TESTEXE) $(LIBDIR)/$(TESTSRC).o

$(LIBDIR)/$(TESTSRC).o: $(TESTDIR)/$(TESTSRC).c 
	@$(CC) -c $^ -o $@ $(IFLAGS) $(CFLAGS) $(LDFLAGS)

# Rule for build artifacts clean
clean:
	$(info  Cleaning files...)
	@rm -rvf $(BINDIR)/* $(LIBDIR)/*
	$(info Done!)

.PHONY:  all clean tests
