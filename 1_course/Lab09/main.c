#include <stdio.h>
#include <stdbool.h> 
#include "library.h"
int main() {
    const int i0=20,j0=0,l0=11;
    struct result begin={i0,j0,false,0};
    struct result res=check(begin,l0);
    printer(res,l0);
    return 0;
}