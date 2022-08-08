.PHONY: all clean

answer: main.o queue.o
		gcc -o answer main.o queue.o
main.o: main.c queue.h
		gcc -c main.c
queue.o: queue.c queue.h
		gcc -c queue.c
clean:
		rm -f *.o answer