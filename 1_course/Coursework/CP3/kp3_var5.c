#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double macheps()
{
	double e = 1.0;
	while (1.0 + e / 2.0 > 1.0)
		e /= 2.0;
	return e;
}


struct Point {
	double x;
	double y;
};
long long factorial(int n){
    long long result=1;
    for (int i=1;i<=n;i++){
        result = result*i;
    }
    return result;
}
double taylor_function(unsigned n, double x)
{
	double y = 0.;
	for(unsigned i = 1; i <= n; ++i) {
        if (i % 2 == 0){
		    y = y + pow(2*x,2*i)/(factorial(2*i));
        }
        else{
            y = y + (-pow(2*x,2*i))/(factorial(2*i));
        }
	}
	return y;
}
double function(double x)
{
	return 2*(cos(x)*cos(x)-1);
}


void calculate(unsigned iterationCount, double a, double b, double (*taylor_f)(unsigned, double), double (*real_f)(double))
{
	double step = ( b - a ) / iterationCount;
	struct Point* points = (struct Point*)malloc(sizeof(struct Point) * (iterationCount+1));
	double eps = macheps();
	double x = a;
    points[0].x = x;
    points[0].y = 2*(cos(x)*cos(x)-1);
    printf("%d| %lf %lf %lf\n", 0, x, real_f(x), points[0].y);
    x+=step;
	for(unsigned i = 1; i <= iterationCount; ++i, x+=step) {
        for (unsigned p = 1;(p<100) && (fabs(real_f(x) - taylor_f(p, x)) > eps * 100);p++){
            points[i].x = x;
			points[i].y = taylor_f(p, x);
	    } 
        printf("%d| %lf %lf %lf\n", i, x, real_f(x), points[i].y);
    }
}

int main()
{	
	unsigned n;
	double a = 0.0, b = 0.5;
	scanf("%u", &n);
	calculate(n, a, b, taylor_function, function);
}