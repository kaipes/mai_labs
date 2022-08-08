#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
Iterator begin(struct List* list){
    Iterator answer = {list->head->next};
    return answer;
}
Iterator end(struct List* list){
    Iterator answer = {NULL};
    return answer;
}
Iterator next(Iterator* i){
    i->node = i->node->next;
    Iterator answer = {i->node};
    return answer;
}
Iterator prev(Iterator* i){
    i->node = i->node->prev;
    Iterator answer = {i->node};
    return answer;
}
Iterator last(struct List* list){
    Iterator answer = {list->head};
    return answer;
}
bool Equal(Iterator* left, Iterator* right){
    return left->node == right->node;
}
Iterator push(struct List* list,Iterator* i,int number){
    Iterator temp = {(struct Node*)malloc(sizeof(struct Node*))};
   // if (!temp.node) return end(list);
    temp.node->value = number;
    temp.node->next = i->node;
    temp.node->prev=i->node->prev;
    temp.node->prev->next=temp.node;
    i->node->prev=temp.node;
    list->size++;
    return temp;
}
Iterator delete(struct List* list,Iterator* i){
    Iterator temp = last(list);
    if (Equal(&temp,i)) return temp;
    temp.node = i->node->next;
    temp.node->prev = i->node->prev;
    i->node->next->prev = temp.node->prev;
    i->node->prev->next = temp.node;
    list->size--;
    free(i->node);
    i->node=0;
}
bool empty(struct List* list){
    Iterator one = begin(list);
    Iterator two = last(list);
    return Equal(&one,&two);
}
void initlist(struct List* list){
    list->head =(struct Node*) malloc(sizeof(struct Node*));
    list->size = 0;
    list->head->next = list->head->prev = list->head;
}
void PrintList(struct List* l){
    Iterator a = begin(l);
    Iterator b = last(l);
    if(Equal(&a, &b)) printf("Empty");
    while(!Equal(&a, &b)){
        printf("%d ", a.node->value);
        next(&a);
    }
    printf("\n");
}
Iterator distance(struct List* list, int number){
    Iterator a = begin(list);
    Iterator b = last(list);
    if(Equal(&a, &b)){
        return a;
    }
    while(a.node->value != number){
        next(&a);
        if(Equal(&a, &b)) return a;
    }
    return a;
}
void function(struct List* list,int k){
    if (k<=list->size){
            for (int j=0;j<k;j++){
                Iterator a = begin(list);
                Iterator b = last(list);
                if(!Equal(&a, &b)){
                for (int i=0;i<list->size-1;i++){
                    next(&a);
                    if(!Equal(&a, &b)) break;
                }
            }
            delete(list,&a);
        }
    }
}
void destroy(struct List* list){
    struct Node* i = list->head->next;
    while(i != list->head){
        struct Node* pi = list->head;
        i = i->next;
        free(pi);
    }
    free(list->head);
    list->head = NULL;
    list->size = 0;
}

