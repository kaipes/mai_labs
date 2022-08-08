#include <stdio.h>
#include <stdbool.h>
#include "library.h"

int main(){
    int Size = 50;
    char buffer[Size];
    enum State currentState = Start;
    unsigned count = 0;
    unsigned digit = -2;
    char fdigit;
    char sdigit;
    char pdigit;
    while (fgets(buffer,Size,stdin)!= NULL){
        for (int i=0;i< Size && buffer[i]!= '\0';++i){
        currentState = prog(currentState, buffer[i]);
           if (currentState == FirstDigit){

            fdigit = 'a';
            sdigit = 'a';
            fdigit = buffer[i];
            count += 1;
            digit = -1;

        }
        if (currentState == SecondDigit){

            digit=0;
            bool condition = (fdigit == '1' && buffer[i]>='7')||(fdigit == '7' && buffer[i] <= '7')||((fdigit > '1') && (fdigit < '7'));
            if (condition){
                sdigit=buffer[i];
                count+=1;
                digit=1;  

            } else{

               printf("%c%c",fdigit,buffer[i]);

            }
            pdigit = buffer[i];

        }
        if (currentState == Letter){

            if (count == 2){

                conclusion(fdigit,sdigit);
                digit = 0;

            }
            if (digit == -1){

                printf("%c",fdigit);
                digit=0;

            }
            printf("%c",buffer[i]);
            count = 0;

        }
        if (currentState == EndUnNum){
            
            count = 0;
            if (digit == 1){
                
               printf("%c%c",fdigit,pdigit);

            }
            printf("%c",buffer[i]);

            }
        }
    }
}