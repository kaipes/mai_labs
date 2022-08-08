#include "mlisp.h"
double root(double a, double b);
double half__interval(double a, double b, double fa, double fb);
double __KKD__try(double neg__point, double pos__point);
bool close__enough_Q(double x, double y);
double average(double x, double y);
double f(double z);
extern double tolerance;
extern double total__iterations;

double root(double a, double b) {
    double temp (0.);
    temp = half__interval(a, b, f(a), f(b));
    display("Total number of iteranions=");
    display(total__iterations); newline();
    display("[");
    display(a);
    display(" , ");
    display(b);
    display("]");
    return temp;
}

double half__interval(double a, double b, double fa, double fb) {
    double root(0.);
    total__iterations = 0.;
    root = (fa < 0. and  fb > 0. ? __KKD__try(a,b) 
        : fa > 0. and fb < 0. ? __KKD__try(b,a)
        : (b + 1.));
    newline();
    return root;
}

double __KKD__try(double neg__point, double pos__point) {
    double midpoint(0.);
    double test__value(0.);
    midpoint = average(neg__point, pos__point);
    return (close__enough_Q(neg__point, pos__point) ? midpoint
        : (test__value = f(midpoint) , display("+"), total__iterations = total__iterations + 1.0, test__value > 0. ? __KKD__try(neg__point, midpoint)
        : (test__value < 0. ? __KKD__try(midpoint, pos__point)
        : midpoint)
        ));
}

bool close__enough_Q(double x, double y) {
    return (abs(x - y) < tolerance);
}

double average(double x, double y) {
    return ((x + y) * (1.0 / 2.0));
}

double tolerance = 0.001;
double total__iterations = 0.;

double f(double z) {
    return (exp(-z) + sin(z) + 0.75);
}

int main() {
    display("Variant 208-09"); newline();
    display(root(4.72, 6.));
    newline();
    display("(c) Kirill Kashirin 2022"); newline();
}