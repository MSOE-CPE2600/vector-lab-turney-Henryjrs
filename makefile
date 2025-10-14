/*make_minimum_required(VERSION 4.0)
project(Lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab5 VectorCalc.c
        VectorCalc.h
        Vector.cpp
        VectorMem.h
        VectorMem.cpp
        VectorUI.cpp
        VectorUI.h)
*/


CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= VectorCalc.c, Vector.c, VectorMem.c, VectorUI.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=exename

all: $(SOURCES) $(EXECUTABLE) 

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d
       
