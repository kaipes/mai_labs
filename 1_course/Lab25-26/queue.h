#include<stdio.h>
#include<stdlib.h>
struct Token {
    int value;
};
struct Queue {
    struct Token* nodes;
    unsigned capacity;
    unsigned size;
};
void init(struct Queue* queue);
void isempty(struct Queue* queue);
void push_back(struct Queue* queue, struct Token element);
struct Token pop_front(struct Queue* queue);
void printqueue(struct Queue* queue);
void procedure(struct Queue* queue);
void bubblesort(struct Queue* queue);