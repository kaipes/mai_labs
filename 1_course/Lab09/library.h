#include<stdio.h>
#include <stdbool.h> 
int treygolnik1(int i1,int j1,int l1);
int treygolnik2(int i1,int j1,int l1);
int nexti(int i0,int j0, int l0, int k);
int nextj(int i0, int j0, int l0, int k);
int nextl(int i0,int j0,int l0,int k);
int max(int a,int b);
int min(int a,int b);
int abs(int n);
int sign(int n);
struct result{
    int i;
    int j;
    bool inside;
    int stepnum;
};
struct result check(struct result begin,int l0);
void printer(struct result res,int l1);