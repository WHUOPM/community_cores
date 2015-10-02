#!/bin/bash

CC=g++
CFLAGS= -ansi -O5 -Wall
LDFLAGS= -ansi -lm -Wall
EXEC=convert density
OBJ1= graph_binary.o
OBJ2= graph.o

all: $(EXEC)


convert : $(OBJ2) main_convert.o
	$(CC) -o $@ $^ $(LDFLAGS)

density : $(OBJ1) main_density.o
	$(CC) -o $@ $^ $(LDFLAGS)


##########################################
# Generic rules
##########################################

%.o: %.cpp %.h
	$(CC) -o $@ -c $< $(CFLAGS)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o *~ $(EXEC)
