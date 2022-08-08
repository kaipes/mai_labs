#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
Iterator begin(struct List* list) {
    if (!list || !list->head) {
        return NULL;
    }
    return list->head;
}
Iterator next(Iterator it) {
    return it->next;
}
Iterator prev(Iterator it) {
    return it->prev;
}
Iterator plus(Iterator it, int number) {
    for (int i = 0; i < number; i++) {
        it = it->next;
    }
    return it;
}
Iterator end(struct List* list) {
    return NULL;
}
void InitList(struct List* list){
    list->head =(struct Node*) malloc(sizeof(struct Node));
    list->size = 0;
    list->head->next = list->head->prev = list->head;
}
void PushBack(struct List* list, key key) {
    Iterator it = begin(list);
    if (list->size!=0){
        Iterator last = plus(it,list->size);
        last->next = (struct Node*)malloc(sizeof(struct Node));
        last->next->value = key;
    } else {
        it->next = (struct Node*)malloc(sizeof(struct Node));
        it->next->value = key;
        it->next->prev = prev(it);
    }
    ++(list->size);
}
void PopBack(struct List* list) {
    if (list->size!=0){ 
        Iterator it = begin(list);
        it = plus(it, list->size - 1);
        if (list->size!=1) free(it->prev);
        free(it->next);
        list->size--;
    }
}
void destroy (struct List* list) {
    int size = list->size;
    for (int i = 0; i < size; i++) {
        PopBack(list);
    }
}
void PrintList(struct List* list) {
    if (list->size == 0) {
        printf("Empty\n");
    } else {
    Iterator it = begin(list);
    for (int i = 0; i < list->size; i++){
        it = next(it);
        printf("%d %s\n", it->value.k, it->value.value);
        }
    }
}
int distance(Iterator a, Iterator b) { 
    int d = 0;
    Iterator it = a;
    while (it!=b) {
        d+=1;
        it = next(it);
    }
    return d;
}
void BinarySearch(Iterator begin, Iterator end, int x) {
    int left = 0;
    int right = distance(begin,end);
    int search = -1;
    Iterator mid;
    while (left <= right) {
        int middle = (left + right) / 2;
        mid = begin;
        mid = plus(mid,middle);
        if (mid->value.k == x) {
            search = middle;
            break;
        } 
        if (mid->value.k > x){
            right = middle -1;
        } else {
            left = middle+1;
        }
    }
    if (search == -1) {
        printf("Not in List\n");
    } else {
        printf("%d %s\n",x,mid->value.value);
    }
}
void swap (Iterator one,Iterator two, int x, int y) {
    int key;
    char data[50];
    key = one->value.k;
    for (int i =0;i<50;i++){
        data[i] = one->value.value[i];
    }
    one->value.k = two->value.k;
    for (int i=0;i<50;i++){
        one->value.value[i]=two->value.value[i];
    }
    two->value.k = key;
    for (int i=0;i<50;i++){
        two->value.value[i]=data[i];
    }
}
/*void bubble_sort(struct List* list){
    Iterator start = begin(list);
    Iterator finish = begin(list);
    Iterator a; Iterator b;
    finish = plus(start,list->size-1);
    for (int i=1;i<list->size;i++){
        for (int j=1;j<list->size;j++){
            a = begin(list);
                a =plus(a, i);
                b = begin(list);
                b = plus(b, j);
                if (a->value.k < b->value.k){
                    int x = distance(start,a);
                    int y = distance(start,b);
                    swap(list,x, y);
                }
        }
    }
}*/
void SortShell(Iterator start,Iterator finish){
    Iterator a, b;
    for (int i = (distance(start, finish) - distance(start, start) + 1) / 2; i > 0; i /= 2) {
        for (int j = 0; j < (distance(start, finish) - distance(start, start) + 1); j++) {
            for (int z = j + i; z < (distance(start, finish) - distance(start, start) + 1) ; z += i) {
                a = start;
                a = plus(a, j + distance(start, start));
                b = start;
                b = plus(b, z + distance(start, start));
                if (a->value.k > b->value.k) {
                    int x = distance(start,a);
                    int y = distance(start,b);
                    Iterator one = start;
                    one = plus(one, x);
                    Iterator two = start;
                    two = plus(two, y);
                    swap(one,two,x, y);
                }
            }
        }
    }
} 
void LinearSearch(Iterator begin, Iterator end, int x){
    Iterator it = begin;
    bool check = 0;
    char data[50];
    if (it->value.k == x) {
        for (int i=0;i<50;i++){
            data[i]=it->value.value[i];
        }
        check = 1;
    }
    while (it!=end) {
        it = next(it);
        if (it->value.k == x) {
         for (int i=0;i<50;i++){
            data[i]=it->value.value[i];
        }
        check = 1;
        }
    }
    if (check == 1) {
        printf("%d %s\n",x,data);
    } else {
        printf("Not in list\n");
    } 
}