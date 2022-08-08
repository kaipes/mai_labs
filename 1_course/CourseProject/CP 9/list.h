#include <stdbool.h>
typedef struct{
    int k;
    char value[50];
} key;
struct Node{
    key value;
    struct Node* next;
    struct Node* prev;
};
struct List{
    int size;
    struct Node* head;
};
typedef struct Node* Iterator;
Iterator begin(struct List* list);
Iterator end(struct List* list);
Iterator next(Iterator i);
Iterator prev(Iterator i);
Iterator plus(Iterator it, int number) ;
void InitList(struct List* list);
void PrintList(struct List* l);
int distance(Iterator a, Iterator b);
void destroy(struct List* list);
void PushBack(struct List* list, key t);
void PopBack(struct List* list);
void BinarySearch(Iterator begin, Iterator end, int x);
void SortShell(Iterator start,Iterator finish);
void LinearSearch(Iterator begin_it, Iterator end_it, int key);
void swap(Iterator one,Iterator two, int x, int y);