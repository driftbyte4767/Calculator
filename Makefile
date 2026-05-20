CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk+-3.0) -Wall -Wextra
LIBS = $(shell pkg-config --libs gtk+-3.0) -lm

SRC = main.c state.c calc.c
TARGET = calculator

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)