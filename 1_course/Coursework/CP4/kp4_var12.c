#include <stdio.h>
#include <math.h>
double f(double x){
    return log(x)+1.8;
}
double derivative(double x){
    return 1/x-1;
}
double macheps(){
	double e = 1.0;
	while (1.0 + e / 2.0 > 1.0)
		e /= 2.0;
	return e;
}
double it(double x, double y,double eps){
    for (unsigned i = 1;fabs(x-y)>=eps*100;i+=1){
        x = y;
        y = f(x);
        printf("%d | %lf %lf %lf\n",i,y,2.8459,y-2.8459);
    }
    return y;
}
int main(){
    double a = 2;
    double b = 3;
    double x = (a+b)/2;
    double y = f(x);
    double eps = macheps();
    double answer = it(x,y,eps);
    printf("x = %lf\n",answer);
}