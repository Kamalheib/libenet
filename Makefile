CC=gcc
CFLAGS=-Wall
INC=-Iinclude
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
OUT=lib/libenet.a
LDFLAGS= -static

all: $(OUT)

.c.o:
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
	ar rcs $(OUT) $(OBJECTS)
clean:
	rm -f $(OBJECTS) $(OUT)
