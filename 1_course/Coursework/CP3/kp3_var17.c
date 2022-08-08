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

double taylor_function(unsigned n, double x)
{
	double y = 0.;
	for(unsigned i = 0; i <= n; ++i) {
        y=y+pow((x-1)/(x+1),2*i+1)/(2*i+1);
    }
return y;
}
double function(double x)
{
	return 0.5*log(x);
}


void calculate(unsigned iterationCount, double a, double b, double (*taylor_f)(unsigned, double), double (*real_f)(double))
{
	double step = ( b - a ) / iterationCount;
	struct Point* points = (struct Point*)malloc(sizeof(struct Point) * (iterationCount+1));
	double eps = macheps();
	double x = a;
    points[0].x = x;
    points[0].y = 0.5*log(x);
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
	double a = 0.2, b = 0.7;
	scanf("%u", &n);
	calculate(n, a, b, taylor_function, function);
}