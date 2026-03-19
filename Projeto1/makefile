all: graph.o main.o
	gcc graph.o main.c -o main -std=c99 -Wall -lm

graph.o:
	gcc -c graph.c -o graph.o

run:
	./main
clean:
	rm graph.o
	rm main
