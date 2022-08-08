#include <stdio.h>
#include <unistd.h>
using namespace std;
int main(){
    long double a;
    char c;
    long double res = 0;
    int k = 0;
    while(scanf("%Lf%c", &a, &c) != EOF) {
        if (k == 0){
            if (a!=0) {
                res = a;
                k=1;
            } else {
                res = a;
                k=2;
            }
        } else {
            if (a!=0){
                res/=a;
            } else {
              printf("You can't divide it by zero\n");
              break;
            } 
        }
        if(c == '\n') {
            printf("%Lf\n",res);
            k=0;
            fflush(stdout);
            res = 0.;
            continue;
        }
    }
    //cout << res << endl;
    close(STDOUT_FILENO);
    return 0;
}