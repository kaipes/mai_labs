#include<stdio.h>
#include<stdlib.h>
#include "queue.h"
void init(struct Queue* queue){
    queue->capacity = 2;
    queue->size = 0;
    queue->nodes = (struct Token*)malloc(sizeof(struct Token)*queue->capacity);
};
void isempty(struct Queue* queue){
    if (queue->size==0){
        printf("The queue is empty\n");
    } else printf("The queue is not empty\n");
}
void push_back(struct Queue* queue, struct Token element){
    if (queue->size == queue->capacity){
        queue->capacity *=2;
        queue->nodes = (struct Token*)realloc(queue->nodes,sizeof(struct Token)*queue->capacity);
    }
    if (queue->size!=0){
        for (int i=queue->size;i>0;i--){
            queue->nodes[i]=queue->nodes[i-1];
        }
        queue->nodes[0]=element;
        queue->size++;
    } else queue->nodes[queue->size++] = element; 
}
struct Token pop_front(struct Queue* queue){
    if (queue->size == 0){
        printf("Queue is empty\n");
    } else {
        return queue->nodes[--queue->size];
    }
}
void printqueue(struct Queue* queue){
    if (queue->size!=0){
    for (int i=0;i<queue->size;i++){
        printf("%d ",queue->nodes[i].value);
    }
    printf("\n");
    } else printf("Queue is empty\n");
}
void procedure(struct Queue* queue){
    for (int i=0;i<queue->size-1;i++){
           if (queue->nodes[i].value < queue->nodes[i + 1].value){
                struct Token temp = queue->nodes[i];
                queue->nodes[i] = queue->nodes[i + 1];
                queue->nodes[i + 1] = temp;
            }
    }
}
void bubblesort(struct Queue* queue){
    for (int j=0;j<queue->size-1;j++){
        procedure(queue);
    }
}
