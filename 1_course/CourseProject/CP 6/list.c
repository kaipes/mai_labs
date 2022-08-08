#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
Iterator begin(struct List* list){
    if (!list || !list->head) {
        return NULL;
    }
    return list->head;
}
Iterator end(struct List* list){
    return NULL;
}
Iterator next(Iterator i){
    return i->next;
}
Iterator prev(Iterator i){
    return i->prev;
}
Iterator plus(Iterator i,int number){
    for (int j=0;j<number;j++) {
        i=i->next;
    }
    return i;
}
void InitList (struct List* list) {
    list->head =(struct Node*) malloc(sizeof(struct Node*));
    list->size = 0;
    list->head->next = list->head->prev = list->head;
}
void PushBack(struct List *list,Person person){
        Iterator it = begin(list);
        if (list->size!=0){
            Iterator last = plus(it,list->size);
            last->next = (struct Node*)malloc(sizeof(struct Node));
            last->next->data = person;
        } else {
            it->next = (struct Node*)malloc(sizeof(struct Node));
            it->next->data = person;
        }
    ++(list->size);
}
void PrintList(struct List* list) {
    if (list->size == 0) {
        printf("Empty");
    } else {
        printf("| Surname | Initials | Item | Weight | Destination | Time | Transfer | Children | \n");
        Iterator it = begin(list);
        for (int i = 0; i < list->size; i++) {
            it = next(it);
            printf("%9s %7s %8d %7d %12s %8d %8s %9d\n",it->data.surname, it->data.init, it->data.item, it->data.weight, it->data.destination, it->data.time, it->data.transfer, it->data.children);
        }
    }
    printf("\n");
}
void DestroyList(struct List *list){
    while (list->size!=0){
        Iterator it = begin(list);
        it = plus(it, list->size);
        free(it->next);
        list->size--;
    }
    free(list->head);
}
void FunctionList(struct List* list, int p1,int p2) {
    Iterator it = begin(list);
    printf("| Surname | Initials | Item | Weight | Destination | Time | Transfer | Children | \n");
     for (int i = 0; i < list->size; i++) {
        it = next(it);
        if (it->data.item==p1 && it->data.weight>=p2){
        printf("%9s %7s %8d %7d %12s %8d %8s %9d\n",it->data.surname, it->data.init, it->data.item, it->data.weight, it->data.destination, it->data.time, it->data.transfer, it->data.children);
        }
    }
    printf("\n");
}