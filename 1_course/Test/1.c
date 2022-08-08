#include <stdio.h>
const int int_max=1000;
int main(){
    int n;
    int a[int_max];
    int b[int_max];
    int c[int_max];
    scanf("%d",&n);
    int k=0;
    int l=0;
    for (int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for (int i=0;i<n;i++){
        scanf("%d",&b[i]);
    }
    int s=0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (a[i]==b[j]){
                c[k++]=a[i];
            }
        }
    }
    int mx=c[0];
    for (int i=0;i<n;i++){
        if (c[i]>mx){
            mx=c[i];
        }
    }
    int g[mx+1];
    for (int i=0;i<mx+1;i++){
        g[i]=0;
    }
    for (int i=0;i<k;i++){
        g[c[i]]+=1;
    }
    if (k!=0){
    for (int i=0;i<mx+1;i++){
        if (g[i]>0){
            printf("%d ", i);
        }
    }
    }
    printf("\n");
}