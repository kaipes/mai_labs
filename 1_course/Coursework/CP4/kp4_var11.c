#include <stdio.h>
#include <math.h>
double f(double i){
    return exp(i)+sqrt(1+exp(2*i))-2;
}
double macheps(){
	double e = 1.0;
	while (1.0 + e / 2.0 > 1.0)
		e /= 2.0;
	return e;
}
double d(double x,double y,double eps,int n,double k){
    for (double i = 0 ;fabs(x-y)>=eps*100;){
        if ((f(x)*f((x+y)/2))>0){
            x=(x+y)/2;k=x;
        } else if ((f(y)*f((x+y)/2))>0) {
            y=(x+y)/2;k=y;
        }
        n+=1;
        printf("%d | %lf %lf %lf\n",n,k,-0.2877,k+0.2877);
    }
    return x;
}
int main(){
    int n;
    double a = -1;
    double b = 0;
    double x,y,k;
    double eps=macheps();
    x=a;y=b;
    double answer = d(x,y,eps,n,k);
    printf("x = %lf\n",answer);
}