#include <stdio.h>
#include "library.h"
#include <stdbool.h>
int main(){
    unsigned code,det = 0,counter = 0;
    unsigned char buffer[50];
    unsigned bufferSize = 50;
    struct Bitset current;
    init(&current);
    struct Bitset bs;
    init(&bs);
    unsigned char letter[2];
    letter[0]=0;
    letter[1]=0;
    const char* vowels = "аоуэыиАОУЭЫИ";
    struct Bitset vowelset;
    init(&vowelset);
    for (unsigned i = 0; i < 24;i++){
        letter[counter] = vowels[i];
        ++counter;
        if (counter == 2){
            code = utf8ToUnicode(letter[0],letter[1]);
            addElement(&vowelset,code);
            counter = 0;
            letter[0] = 0;
            letter[1] = 0;
        }
    }
    counter=0;
    const char* removevowels = "еюяЕЮЯ";
    struct Bitset removevowelset;
    init(&removevowelset);
    for (unsigned i = 0;i<12;i++){
        letter[counter] =removevowels[i];
        ++counter;
        if (counter == 2){
            code = utf8ToUnicode(letter[0],letter[1]);
            addElement(&removevowelset,code);
            counter = 0;
            letter[0] = 0;
            letter[1] = 0;
        }
    }
    counter = 0;
    letter[0] = 0;
    letter[1] = 0;
    unsigned k=0;
    unsigned f=0;
    while (fgets(buffer, bufferSize, stdin) != NULL) {
    	for (int i = 0; i < bufferSize; ++i){
        if (buffer[i]!=' ' && buffer[i]!='\n' && buffer[i]!='\0'){    
           letter[counter] = buffer[i];
           ++counter;
           if (counter == 2){
               code = utf8ToUnicode(letter[0],letter[1]);
               addElement(&current,code);
               addElement(&bs,code);
               if ((code == 1025) || (code == 1105)){
                   f=-1;
               }
               counter = 0;
               letter[0] = 0;
               letter[1] = 0;
            }
        }
        if (buffer[i]==' ' || buffer[i]=='\0' || buffer[i]=='\n'){
            struct Bitset bs;
            bs=current;
            makeIntersect(&bs,vowelset);
            makeIntersect(&current,removevowelset);
              if (bs.set!=0 && current.set == 0 && f!=-1){
                  det+=1;
              }
            init(&current);
            init(&bs);
            f=0;  
        }
        if (buffer[i]=='\0'){
            break;
        }
        }
    }
    if (det>0){
        printf("Есть слово, содержащее гласные только 1-го рода\n");
    } else {
        printf("Нет слов, содержащие гласные только 1-го рода\n");
    }
}