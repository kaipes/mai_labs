#include <math.h>

float SinIntegral(float A, float B, float e){
        float integral = 0;
        for(float i = A; i < B; i+=e ){
                integral += sin(i) * e;
        }
        return integral;
}

float E(int x) {
        return pow(1 + 1. / x, x);
}