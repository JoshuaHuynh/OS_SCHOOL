# Name: Joshua Huynh
# Project: Lab 2

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES and EXECUTABLES2 are each a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES=launch
SRC=Launch.c
OBJ=Launch.o

EXECUTABLES2=tube
SRC2=Tube.c
OBJ2=Tube.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g

# Here are my default targets for the Makefile.  
all: $(EXECUTABLES) $(EXECUTABLES2)



# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXECUTABLES): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -Wall -Wextra
	$(CC) $(CFLAGS) -o $@ $(OBJ) -Wall -Wextra

$(EXECUTABLES2): $(SRC2)
	$(CC) $(CFLAGS) -c $(SRC2) -Wall -Wextra
	$(CC) $(CFLAGS) -o $@ $(OBJ2) -Wall -Wextra

# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLES) $(OBJ) *~
	rm -f $(EXECUTABLES2) $(OBJ2) *~
