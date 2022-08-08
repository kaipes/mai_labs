#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(){
    struct List list;
    InitList(&list);
    int symbol;
    bool sorted = false;
    while ((symbol = getchar()) != EOF){
        switch(symbol){
            case '+':{
                key key;
                scanf("%d %s",&key.k, key.value);
                PushBack(&list,key);
                break;
            }
           case 'p':{
                PrintList(&list);
                break;
            }
            case '-':{
                PopBack(&list);
                break;
            }
            case '?':{
                if (list.size == 0) {
                    break;
                }
                int start, finish, x;
                scanf("%d %d %d", &start, &finish, &x);
                Iterator a = begin(&list);
                Iterator b = begin(&list);
                a = plus(a,start);
                b = plus(b,finish);
                if (sorted == true){ 
                    (BinarySearch(a,b,x));
                } else {
                    LinearSearch(a,b,x);
                } 
                break;
            }
            case 's': {
                Iterator start = begin(&list);
                Iterator finish = begin(&list);
                finish = plus(start,list.size);
                SortShell(start,finish);
                sorted = true;
                break;
            }
        }
    }
    destroy(&list);
} 