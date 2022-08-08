#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct vector_int {
    int number_of_elements;
    int capacity;
    int *elem;
} vector_int;

const int INF = 1e9 + 7;
int is_vector_empty(vector_int *v)
{
    if (v->number_of_elements == 0) {
        return 1;
    }
    return 0; 
}

int size(vector_int *v)
{
    return v->capacity;
}

void vector_create_int(vector_int *v, int size)
{
    v->capacity = size;
    v->number_of_elements = 0;
    v->elem = (int*)malloc(sizeof(int) * (v->capacity+1));
}
void resize_int(vector_int *v,int size)
{
    v->capacity = size;
    v->elem = (int*)realloc(v->elem, sizeof(int) * (v->capacity));
}
void vector_push_back_int(vector_int *v, int c)
{
    if (v->number_of_elements == v->capacity) {
        resize_int(v,v->capacity+1);
    }
    v->elem[v->number_of_elements - 1] = c;
    v->number_of_elements++;
}
void vector_print_int(vector_int *v,int c)
{
    for (int i = 0; i < c; ++i) {
        printf("%d ", v->elem[i]);
    }
    printf("\n");
}
int main()
{  
    int n, m, A_lenght = 1,x;
    scanf("%d %d",&n,&m);
    vector_int A,M,wide,sum,answer;
    int count_in_line = 0, max_in_line = 0, a1 = 1, a2 = 2, a3 = 3, a3_changed = 0, M_changed = 0;
    printf("n = %d, m = %d\n", n, m);
   // int wide[n], sum[n], answer[n];
   /* for (int i=0;i<n;i++){
        answer[i]=0;
    } */
    vector_create_int(&A,A_lenght);
    vector_create_int(&M,n);
    vector_create_int(&wide,n);
    vector_create_int(&sum,n);
    vector_create_int(&answer,n);
    for (int i=0;i<n;i++){
        answer.elem[i]=0;
    }
    for (int i = 0; i < n; ++i) {
        M.elem[i] = 0;
    }
    for (int i = 0; i < A_lenght; ++i) {
        A.elem[i] = -INF;
    }
    printf("Your matrix:\n");
    for (int i = 0; i < n; ++i) {
        wide.elem[i] = 0;
        sum.elem[i] = 0;
        for (int j = 0; j < m; ++j) {
            scanf("%d", &x);
            if (x != 0) {
                wide.elem[i] += 1;
                A_lenght += 3;
                resize_int(&A,A_lenght);
                if (a3_changed) {
                    A.elem[a3] = a1; a3 += 3;
                }
                ++count_in_line;
                if (!M_changed) {
                    A.elem[a3 - 3] = 0;
                    M.elem[i] = a1;
                    M_changed = 1;
                }
                A.elem[a1] = j; a1 += 3;
                A.elem[a2] = x; a2 += 3;
                A.elem[a3] = 0;
                a3_changed = 1;
            }
             sum.elem[i] += x;
        }
        if (max_in_line < count_in_line) {
            max_in_line = count_in_line;
        }
        if (count_in_line == 0) {
            M.elem[i] = 0;
        }
        if (wide.elem[i] == max_in_line){
            answer.elem[i] = sum.elem[i];
        }
        count_in_line = 0;
        M_changed = 0;
    }
    A.elem[0] = 0;
    printf("M: ");
    vector_print_int(&M,n);
    printf("A: ");
    vector_print_int(&A,A_lenght);
 //   solve(A_lenght, n, &A, &M);
 /*   for (int i=0;i<n;i++){
        printf("%d ", wide[i]);
    }
    printf("\n");
    for (int i=0;i<n;i++){
        printf("%d ",answer[i]);
    } */
    int mx = 0;
    for (int i=0;i<n;i++){
       if (wide.elem[i]>mx){
           mx = wide.elem[i];
       }
    }
    for (int i=0;i<n;i++){
        if (mx == wide.elem[i]){
            printf("Line %d has %d elements, their sum = %d\n", i+1, wide.elem[i], answer.elem[i]);
        }
    }
    int matrix[n][m];
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            matrix[i][j]=0;
        }
    }
    int j=0;
    int z=0;
    for (int i=1;i<A_lenght;i+=3){
        z=A.elem[i];
        matrix[j][z]=A.elem[i+1];
      //  printf("%d!",i+2);
        if ((A.elem[i+2])==0) j+=1;
    }
    printf("Original matrix\n");
    for (int k=0;k<n;k++){
        for (int l=0;l<m;l++){
            printf("%d ",matrix[k][l]);
        }
        printf("\n");
    }
    free(A.elem);
    free(M.elem);
    free(wide.elem);
    free(sum.elem);
    free(answer.elem);
    return 0;
}