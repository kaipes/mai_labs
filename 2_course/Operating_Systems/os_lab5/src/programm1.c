#include<stdio.h>

float SinIntegral(float A,float B,float e);
float E(int x);

int main(){
    int key;
    while(scanf("%d",&key)>0){
        if (key == 1) {
            float A,B,e;
            scanf("%f%f%f",&A,&B,&e);
            printf("%s(%f, %f, %f) = %f\n","SinIntegral",A,B,e,SinIntegral(A,B,e));
        } else if (key == 2) {
            int x;
            scanf("%d",&x);
            printf("%s(%d) = %f\n","E",x,E(x));
        } else {
            printf("ERROR");
        }
    }
}