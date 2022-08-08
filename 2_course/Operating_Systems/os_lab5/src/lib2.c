#include <math.h>

float SinIntegral( float A, float B, float e){
        float integral = 0;
        for(float i = A + e; i < B; i+=e ){
                integral += (sin(i) + sin(i - e)) / 2 * e;
        }
        return integral;
}

float E(int x) {
        float answer = 0;
        long long s = 1;
        for (int i = 0; i <= x; ++i) {
            if (i!=0) {
                s*=i;
            }
            answer += 1. / s;
        }
        return answer;
}
