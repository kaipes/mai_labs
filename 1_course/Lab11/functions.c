#include <stdio.h>
#include <stdbool.h>
#include "library.h"


enum State prog(enum State currentState,char currentSymbol)
{
    enum State newState;
    switch(currentState){
        case Start:
        {
            
            if (currentSymbol > '0' && currentSymbol < '8'){

                newState = FirstDigit;

            } else{
                
                newState = Letter;
            }
            break;

        }
        case Letter:
        {

            if (currentSymbol > '0' && currentSymbol < '8'){

                newState = FirstDigit;

            } else{
                
                newState = Letter;

            }
            break;

        }
        case FirstDigit:
        {
          
           if (currentSymbol >='0' && currentSymbol <='9'){

                newState = SecondDigit;

            } else{
                
                newState = Letter;

            }
            break;

        }
        case SecondDigit:
        {
            if (currentSymbol >= '0' && currentSymbol <= '9'){

                newState = EndUnNum;

            } else{
                newState = Letter;
            
            }
            break;

        }
        case EndUnNum:
        { 
            
            if (currentSymbol >= '0' && currentSymbol <= '9'){

                newState = EndUnNum;

            } else{
                
                newState = Letter;

            }
            break;

        }
    }
    return newState;
}
void conclusion(char c,char d){
    if (c=='1' && d=='7'){

        printf("семнадцать");

    }
    else if (c=='1'&& d=='8'){
        
        printf("восемнадцать");

    }
    else if (c=='1'&& d=='9'){
        
        printf("девятнадцать");

    }
    else{
        
        if (c=='2'){
            
            printf("двадцать");

        }
        if (c=='3'){ 
            
            printf("тридцать");

        }
        if (c=='4'){ 
            
            printf("сорок");

        }
        if (c=='5'){ 
            
            printf("пятьдесят");

        }
        if (c=='6'){
            
            printf("шестьдесят");

        }
        if (c=='7'){ 
            
            printf("семьдесят");

        }
        if (d=='1'){
            
            printf(" один");
        
        }
        if (d=='2'){ 
            
            printf(" два");

        }
        if (d=='3'){
            
            printf(" три");

        }
        if (d=='4'){
            
            printf(" четыре");

        }
        if (d=='5'){
            
            printf(" пять");

        }
        if (d=='6'){
            
            printf(" шесть");

        }
        if (d=='7'){
            
            printf(" семь");

        }
        if (d=='8'){
            
            printf(" восемь");

        }
        if (d=='9'){
            
            printf(" девять");
        }
    }
}