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

# Unity test framework source
UNITYDIR := ../Unity/src

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
LDFLAGS= -L$(BINDIR) -l$(LIBNAME)

#
# Compilation Rules
#

$(info ----- TinyNoise -----)

default: help

# Help message 
help:
	@echo "- Target rules:"
	@echo "    all      - Cleans, compiles and test the library"
	@echo "    lib      - Compiles the static library"
	@echo "    tests    - Compiles with Unity and run tests binary file"
	@echo "    clean    - Removes all build artifacts from lib and build folders"
	@echo "    help     - Prints a help message with target rules (Default)"

# Rule for cleaning, building and testing library
all: clean tests
	$(info Done!)

# Rule for building objects and static library
lib: lib$(LIBNAME).a
	$(info Done!)

# Rule for static library build
lib$(LIBNAME).a: $(OFILES)
	$(info Building the library...)
	@ar rcs $(BINDIR)/lib$(LIBNAME).a $(OFILES) 

# Rule for object binaries compilation
$(LIBDIR)/%.o: $(SRCDIR)/%.c
	$(info Compiling source files...)
	@$(CC) -c $^ -o $@ $(CFLAGS)

# Rule for test executable build
tests: lib$(LIBNAME).a $(BINDIR)/$(TESTEXE)
	$(info Running tests...)
	@./$(BINDIR)/$(TESTEXE)
	
$(BINDIR)/$(TESTEXE): $(LIBDIR)/$(TESTSRC).o $(LIBDIR)/unity.o
	$(info Building test executable...)
	@$(CC) $^ $(LDFLAGS) -o $@  

$(LIBDIR)/$(TESTSRC).o: $(TESTDIR)/$(TESTSRC).c 
	@$(CC) -c $^ -o $@ $(CFLAGS) $(IFLAGS) -I$(UNITYDIR)

$(LIBDIR)/unity.o: $(UNITYDIR)/unity.c 
	@$(CC) -c $^ -o $@ $(CFLAGS) -I$(UNITYDIR)

# Rule for build artifacts clean
clean:
	$(info  Cleaning files...)
	@rm -rvf $(BINDIR)/* $(LIBDIR)/*
	$(info Done!)

.PHONY:  all lib clean tests
