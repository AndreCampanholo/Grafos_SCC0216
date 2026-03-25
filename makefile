# Detectar sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /F /Q
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

CC = gcc
CFLAGS = -std=c99 -Wall
LDFLAGS = -lm

SOURCES = graph.c main.c
OBJECTS = graph.o main.o
TARGET = main$(EXE)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

graph.o: graph.c graph.h
	$(CC) -c graph.c -o graph.o $(CFLAGS)

main.o: main.c graph.h
	$(CC) -c main.c -o main.o $(CFLAGS)

run: $(TARGET)
ifeq ($(OS),Windows_NT)
	$(TARGET)
else
	./$(TARGET)
endif

clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: all run clean