# Filename: VC_makefile
# Description: Makefile for VectorCalc
# Author: Stephen Henry
# Date: 10/3/2025
# How to compile: gcc -o VectorCalc VectorCalc.c Vector.c VectorUI.c VectorMem.c

CC = gcc
CFLAGS = -c -Wall
LDFLAGS =
SOURCES = VectorCalc.c Vector.c VectorUI.c VectorMem.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = VectorCalc

all: $(EXECUTABLE)

-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d
