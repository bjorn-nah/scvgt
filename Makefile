# This Makefile is to use with MINGW

EXECUTABLE=scvgt.exe
 
CC=gcc
LDFLAGS=-lgdi32
INCLUDE_DIRS = -I.\stb_image
 
src = $(wildcard *.c)
obj = $(src:.c=.o)
 
all: scvgt
 
scvgt: $(obj)
	$(CC) $(INCLUDE_DIRS) -o $(EXECUTABLE) $^ $(LDFLAGS) 
 
.PHONY: clean
clean:
	del $(obj) $(EXECUTABLE)