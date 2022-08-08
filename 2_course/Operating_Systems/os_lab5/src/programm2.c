#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[]){

    void *ext_library = NULL;  
    float (*SinIntegral)(float A, float B, float e);
    float (*E)(int x);
    //загрузка библиотеки
    int key; int start_library;
    printf("Enter start library: 1 or 2?");
    scanf("%d",&start_library);
    if (start_library == 1) {
        ext_library = dlopen("/home/kirill/OS/os_lab5/src/libd1.so",RTLD_LAZY);   
    } else if (start_library == 2) {
        ext_library = dlopen("/home/kirill/OS/os_lab5/src/libd2.so",RTLD_LAZY);
    } else {
        printf("You don't write start key\n");
    }
    if (!ext_library){
        fprintf(stderr,"dlopen() error: %s\n", dlerror());
        return 1;
    }
    SinIntegral = dlsym(ext_library,"SinIntegral");
    E = dlsym(ext_library, "E");
    while (scanf("%d",&key) > 0 ) {
        if (key == 1) {
            float A,B,e;
            scanf("%f%f%f",&A,&B,&e);
            printf("%s(%f, %f, %f) = %f\n","SinIntegral",A,B,e,(*SinIntegral)(A,B,e));
        } else if (key == 2) {
            int x;
            scanf("%d",&x);
            printf("%s(%d) = %f\n","E",x,(*E)(x));
        } else if (key == 0) {
            dlclose(ext_library);
            if (start_library == 1) {
                ext_library = dlopen("./libd2.so",RTLD_LAZY);
                start_library = 2;
            } else if (start_library == 2) {
                ext_library = dlopen("./libd1.so",RTLD_LAZY);
                start_library = 1;
            }
            if (!ext_library) {
                fprintf(stderr,"dlopen() error: %s\n", dlerror());
                return 1;
            }
            SinIntegral = dlsym(ext_library,"SinIntegral");
            E = dlsym(ext_library, "E");
        }
    }
    dlclose(ext_library);
}