CC = g++

CFLAGS = -Wall -O3

LDFLAGS =

OBJECTS = main.o fish.o site.o tank.o
FILES = main.cc fish.cc site.cc tank.cc

TARGET = fish_tank

all: $(FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

.PHONY: test mem_test clean

test: all
	./$(TARGET) -m 95000 -t 350 -s 17

mem_test: all
	valgrind ./$(TARGET) -m 900 -t 350 -s 17

clean:
	$(RM) $(OBJECTS) $(TARGET)
