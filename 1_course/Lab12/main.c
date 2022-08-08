#include <stdio.h>
#include "library.h"
int main(){
    long long digit;
    struct Number result = {.size=0,.arr={0}};
    scanf("%lld", &digit);
    struct Number n = init(digit);
    fillarray(&n,&result);
    printNumber(&result);
}