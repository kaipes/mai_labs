#include <stdio.h>
#include <math.h>
double f(double x){
    return 2*x*sin(x)-cos(x);
}
double d(double x){
    return 3*sin(x)+2*x*cos(x);
}
double d1(double x){
    return 5*cos(x)-2*x*sin(x);
}
double macheps(){
	double e = 1.0;
	while (1.0 + e / 2.0 > 1.0)
		e /= 2.0;
	return e;
}
double newton(double x, double y , double eps){
    for (unsigned i = 2;fabs(f(x)*d1(x))>=d(x)*d(x) || (fabs(x-y)>=eps*100);i+=1){
        y = x;
        x = y - f(x)/d(x);
        printf("%d | %lf %lf %lf\n",i,x,0.6533,x-0.6533);
    }
    return x;
}
int main(){
    double a = 0.4;
    double b = 1;
    double x = (a+b)/2;
    double y;
    double eps = macheps();
    printf("%d | %lf %lf %lf\n",1,x,0.6533,x-0.6533);
    double answer=newton(x,y,eps);
    printf("x = %lf\n",answer);
}