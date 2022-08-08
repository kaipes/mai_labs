#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main() {
    struct List list;
    initlist(&list);
    char symbol;
    while ((symbol = getchar()) != EOF) {
        switch(symbol){
            case '+':{
                int position,insert;
                scanf("%d %d",&position,&insert);
                Iterator a = begin(&list);
                Iterator b = last(&list);
                for (int i=1;i<position;i++){
                    if (Equal(&a,&b)) break;
                    next(&a);
                }
                push(&list,&a,insert);
                break;
            }
            case 'p':{
                PrintList(&list);
                break;
            }
            case '-':{
                int number;
                scanf("%d", &number);
                Iterator c = distance(&list, number);
                delete(&list, &c);
                break;
            }
            case 'f':{
                int k;
                getchar();
                scanf("%d",&k);
                function(&list,k);
                break;
            }
            
        }
    }
    destroy(&list);
} 
