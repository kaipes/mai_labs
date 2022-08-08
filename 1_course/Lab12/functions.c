#include <stdio.h>
#include "library.h"
struct Number init(long long a){
    
    struct Number result = {.size=0};
    while(a>0){

        result.arr[result.size++]=a%10;
        a/=10;

    }
    return result;
};
void fillarray(const struct Number* const n,struct Number* result){

    for (int i=0;i<n->size;++i){

        result->arr[n->arr[i]]+=1;

    }
    for (int i=0;i<10;++i){
        if (result->arr[i]>0){
            result->size++;
        }
    }
}
void printNumber(const struct Number* const n){
    if (n->size==10){

        printf("Все цифры встречаются хотя бы один раз");

    }
    else{

        printf("Цифры, которые не встречаются ни разу: ");
        for (int i=0;i<10;++i){
            if (n->arr[i]==0){

                printf("%d ",i);
            
            }
        }
    }
    printf("\n");
}