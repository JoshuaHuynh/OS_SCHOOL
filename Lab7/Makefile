# Name: Joshua Huynh
# Project: Lab 7

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES and EXECUTABLES2 are each a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES=matrix_gen
SRC=matrix_gen.c
OBJ=matrix_gen.o

EXECUTABLES2=matrix_add
SRC2=matrix_add.c
OBJ2=matrix_add.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g

# Here are my default targets for the Makefile.  
all: $(EXECUTABLES) $(EXECUTABLES2)



# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXECUTABLES): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -lrt -Wall -Wextra
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lrt -Wall -Wextra

$(EXECUTABLES2): $(SRC2)
	$(CC) $(CFLAGS) -c $(SRC2) -lrt -Wall -Wextra
	$(CC) $(CFLAGS) -o $@ $(OBJ2) -lrt -Wall -Wextra

# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLES) $(OBJ) *~
	rm -f $(EXECUTABLES2) $(OBJ2) *~
