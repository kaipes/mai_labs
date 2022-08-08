
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct{
    char surname[50];
    char init[10];
    int item;
    int weight;
    char destination[50];
    int time;
    char transfer[10];
    int children;
} Person;
struct Node{
    Person data;
    struct Node* prev;
    struct Node* next;
};
struct List {
    struct Node* head;
    unsigned size;
};
typedef struct Node* Iterator;
Iterator begin(struct List* list);
Iterator next(Iterator it);
Iterator plus(Iterator it,int number);
Iterator end(struct  List* list);
void InitList(struct List* list);
void PushBack(struct List* list, Person person);
void PrintList(struct List* list);
void DestroyList(struct List *list);
void FunctionList(struct List* list, int p1,int p2);
