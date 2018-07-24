CC=gcc
CFLAGS=-Wall
INC=-Iinclude
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
TEST_SRC=$(wildcard test/*.c)
TEST_OBJ=$(TEST_SRC:.c=.o)
TEST_EXEC=test/test
OUT=lib/libenet.so

all: $(OUT) tests

.c.o:
	$(CC) $(CFLAGS) -fPIC $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
#	ar rcs $(OUT) $(OBJECTS)
	$(CC) -shared -o $(OUT) $(OBJECTS)

tests:
	$(CC) $(CFLAGS) $(INC) $(TEST_SRC) $(OUT) -o $(TEST_EXEC)

clean:
	rm -f $(TEST_OBJ) $(OBJECTS) $(OUT) $(TEST_EXEC)
