#include <stdio.h>
#include <stdbool.h> 
#include "library.h"
int max(int a,int b){
    if (a>b) return a;
    else return b;
}
int min(int a,int b){
    if (a<b) return a;
    else return b;
}
int abs(int n){
    if (n>0) return n;
    else return (-1)*n;
}
int sign(int n){
    if (n>0) return 1;
    else if (n<0) return -1;
    else return 0;
}
int treygolnik1(int i1,int j1,int l1){
    return j1+i1-10;
}
int treygolnik2(int i1,int j1,int l1){
    return j1-i1-10;
}
int nexti(int i0,int j0, int l0, int k){
    return ((i0-k)*max(j0,l0)+(j0-k)*min(i0,l0)+(l0-k)*max(i0,j0))%23;
}
int nextj(int i0, int j0, int l0, int k){
    return (-((i0-k)*min(j0,l0)+(j0-k)*max(i0,l0)+(l0-k)*min(i0,j0))%27);
}
int nextl(int i0,int j0,int l0,int k){
    return abs(i0+j0-l0-k)*sign(i0-j0+l0-k);
}
struct result check(struct result begin,int l0){
    int l1=l0;
    struct result res = {20,0,false,0};
    for (unsigned k=0;k<50;++k){
        bool pointinside=((begin.i>=-10)&&(begin.i<=0)&&(begin.j>=0)&&(begin.j<=20)&&(treygolnik1(begin.i,begin.j,l0)<=0)&&(treygolnik2(begin.i,begin.j,l0)>=0));
        if (pointinside){
            res.i=begin.i;
            res.j=begin.j;
            res.inside=true;
            res.stepnum=k;
            break;
        }
        res.i=nexti(begin.i,begin.j,l0,k);
        res.j=nextj(begin.i,begin.j,l0,k);
        l1=nextl(begin.i,begin.j,l0,k);
        begin.i=res.i;
        begin.j=res.j;
        l0=l1;
    }
    return res;
}
void printer(struct result res,int l1) {   
    if (res.inside){
        printf("Попадание!\n");
        printf("Время попадания: %d \n",res.stepnum);
        printf("Координаты: (%d,%d) \n",res.i,res.j);
        printf("Значение динамического параметра движения: %d\n", l1);
    }
    else {
        printf("Промах!\n");
        printf("Шагов пройдено - 50\n");
        printf("Конечные координаты: %d %d\n",res.i,res.j);
        printf("Значение динамического параметра движения: %d\n",l1);
    }
}