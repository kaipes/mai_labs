#include <stdbool.h>
struct Node{
    int value;
    struct Node* next;
    struct Node* prev;
};
struct List{
    int size;
    struct Node* head;
};
typedef struct{
    struct Node* node;
} Iterator;
Iterator begin(struct List* list);
Iterator end(struct List* list);
Iterator next(Iterator* i);
Iterator prev(Iterator* i);
bool Equal(Iterator* left, Iterator* right);
Iterator push(struct List* list,Iterator* i,int number);
Iterator delete(struct List* list,Iterator* i);
bool empty(struct List* list);
void initlist(struct List* list);
void PrintList(struct List* l);
Iterator distance(struct List* list, int number);
void function(struct List* list,int k   );
void destroy(struct List* list);
Iterator last(struct List* list);