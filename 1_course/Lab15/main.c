#include <stdio.h>
int main(){
    int n,max,l=0;
    scanf("%d",&n);
    int a[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    max = a[0][0];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (a[i][j]>max){
                max=a[i][j];
            }
        }
        a[l][l] = max;
        l++;
        max=-1;
    }
    printf("Answer:\n");
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}