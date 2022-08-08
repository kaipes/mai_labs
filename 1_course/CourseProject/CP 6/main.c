#include "person.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char** argv){
    struct List list;
    Person person;
    InitList(&list);
    FILE *file = fopen("test.txt","r");
    int p1 =atoi(argv[2]);
    int p2=atoi(argv[4]);
    if (!file){
        printf("Can not open file\n");
        exit(1);
    }
    while(fscanf(file,"%s %s %d %d %s %d %s %d", person.surname, person.init, &person.item, &person.weight, person.destination, &person.time, person.transfer, &person.children) != EOF){
        PushBack(&list,person);
    }
    PrintList(&list);
    FunctionList(&list,p1,p2);
    DestroyList(&list);
    fclose(file);
}
