#include <stdio.h>
struct Number{

    unsigned size;
    long long arr[30];
    
};
struct Number init(long long a);
void fillarray(const struct Number* const n, struct Number* array);
void printNumber(const struct Number* const n);