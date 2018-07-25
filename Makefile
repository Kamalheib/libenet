CC=gcc
CFLAGS=-Wall
INC=-Iinclude
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
TEST_SRC=$(wildcard test/test.c)
TEST_OBJ=$(TEST_SRC:.c=.o)
TEST_EXEC=test/test
SPI_SRC=$(wildcard test/spi/*.c)
SPI_OBJ=$(TEST_SRC:.c=.o)
SPI_EXEC=test/spi/spi
OUT=lib/libenet.so

all: $(OUT) tests spi

.c.o:
	$(CC) $(CFLAGS) -fPIC $(INC) -c $< -o $@

$(OUT): $(OBJECTS)
#	ar rcs $(OUT) $(OBJECTS)
	$(CC) -shared -o $(OUT) $(OBJECTS)

tests:
	$(CC) $(CFLAGS) $(INC) $(TEST_SRC) $(OUT) -o $(TEST_EXEC)

spi:
	$(CC) $(CFLAGS) $(INC) $(SPI_SRC) $(OUT) -o $(SPI_EXEC)

clean:
	rm -f $(TEST_OBJ) $(OBJECTS) $(OUT) $(TEST_EXEC) $(SPI_EXEC)
