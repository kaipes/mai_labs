#include <stdio.h>
#include "library.h"
int main()
{    
    const unsigned max_size = 1000;
    unsigned n;
    scanf("%d", &n);
    int matrix[max_size][max_size];
    for (unsigned i = 0; i < n; i++){
        for (unsigned j = 0; j < n;j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    unsigned i = 0;
    unsigned j = 0;
    enum State currentState = Start;
    while (currentState!=Finish){
        if (currentState == DiagDown){
            ++i;
            ++j;
            // printf("DiagDown ");
        }
        if (currentState == DiagUp){
            --i;
            --j;
            // printf("DiagUp ");
        }
        if (currentState == MoveUp){
            --i;
            // printf("MoveUp ");
        }
        if (currentState == MoveDown){
            ++i;
            // printf("MoveDown ");
        }
        if (currentState == MoveMirrorDown){
            i = n-1;
            j =  n-1-j;
            // printf("MoveMirrorDown ");
        }
        if (currentState == MoveMirrorUp){
            i=0;
            j=n-1-j;
            // printf("MoveMirrorUp ");
        }
        printf("%d ",matrix[i][j]);
        currentState = nextState(currentState,i,j,n);
    }
    printf("\n");
}