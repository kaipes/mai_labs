#include <iostream>
#include <unistd.h>
#include <sstream>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <fstream>
using namespace std;
int main(){
    const char* in_sem_name = "input_semaphor";
    const char* out_sem_name = "output_semaphor";
    sem_unlink(in_sem_name);
    sem_unlink(out_sem_name);
    sem_t* input_semaphore = sem_open(in_sem_name, O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH, 1);
    sem_t* output_semaphore = sem_open(out_sem_name, O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH, 0);
    std::string filename;
    std::string s;
    int map_fd1 = shm_open("map_fd1.txt", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    int map_fd2 = shm_open("map_fd2.txt", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if(map_fd1 == -1){
        std::cout << "Error during creating/open file1 for file mapping" << endl;
        exit(1);
    }
    if(map_fd2 == -1){
        std::cout << "Error during creating/open file2 for file mapping" << endl;
        exit(1);
    }
    char* memptr_1 = (char*)mmap(nullptr, getpagesize(), PROT_READ | PROT_WRITE,  MAP_SHARED, map_fd1, 0);
    char* memptr_2 = (char*)mmap(nullptr, getpagesize(), PROT_READ | PROT_WRITE,  MAP_SHARED, map_fd2, 0);
    if (memptr_1 == MAP_FAILED){
        cout << "Error in creating file1 mapping << endl";
        exit(1);
    }
    if (memptr_2 == MAP_FAILED){
        cout << "Error in creating file2 mapping" << endl;
        exit(1);
    } 
    cout << "Print name of file: ";
    cin >> filename;
    ifstream file1;
    file1.open(filename, ios_base::in);
    if (!file1) {
        cout << "File not exist!" << endl;
        exit(1);
    }
   
    int id = fork();
    switch(id){
        case -1:
            cout << "Error during creating fork" << endl;
            exit(1);
            break;
        case 0: {
            sem_wait(output_semaphore);
            sem_wait(input_semaphore);
            sem_post(output_semaphore);
            s = "";
            struct stat st;
            if(fstat(map_fd1, &st)){
                cout << "Error during fstat" << endl;
                exit(1); 
            }
            int ind = 0, idx = 0;
            int key = 0, length_1 = 0;
            while(ind <= st.st_size){
                if(memptr_1[ind] != '\n'){
                    s += memptr_1[ind++];
                } else {
                    long double res = 0;
                    string r;int a;
                    int first = 1;
                    s = s + " ";
                    for (unsigned i =0;i<s.length();i++){
                        if (s[i] != ' '){
                            r+=s[i];
                        } else {
                            if (first == 1) {
                                res = stoi(r);
                                first = 0;
                            } else {
                                a = stoi(r);
                                if (a == 0) {
                                    key = 1;
                                    break;
                                } else {
                                    res/=a;
                                }
                            }
                            r ="";
                        }
                    }
                    if (key == 0) {
                        s =  to_string(res);
                    } else {
                        s = "You can not div by zero!";
                        key = 0;
                    }
                    s = s + "\n";
                    length_1 += s.length() * sizeof(char);
                    if(ftruncate(map_fd2, length_1)){
                        cout << "Error during ftruncate" << endl;
                        exit(1);    
                    }
                    for(unsigned i = 0; i < s.length(); i++){
                        memptr_2[idx++] = s[i];
                    }
                    ind++;
                    s = "";
                }
            }
            sem_post(input_semaphore);
            break;
        }
        default: {
            sem_wait(input_semaphore);
            int idx = 0;
            int length = 0;
            sem_post(output_semaphore);
            while(!file1.eof()){
                getline(file1,s);
                if (s!="") {
                    s = s + "\n";
                    length += s.length() * sizeof(char);
                    if(ftruncate(map_fd1, length)){
                        cout << "Error during ftruncate" << endl;
                        exit(1);    
                    } 
                    for(unsigned i = 0; i < s.length(); i++){
                        memptr_1[idx++] = s[i];
                    }
                }
            } 
            sem_post(input_semaphore);
            s = "";
            int ind = 0;
            sem_wait(output_semaphore);
            sem_wait(input_semaphore);
            struct stat st;
            if(fstat(map_fd2, &st)) {
                cout << "Error during fstat" << endl;
                exit(1); 
            }
            while(ind <= st.st_size) {
                if(memptr_2[ind] != '\n') {
                    s += memptr_2[ind++];
                } else {
                    s += "\n";
                    cout << s;
                    ++ind;
                    s = "";
                }
            }
            close(map_fd1);
            close(map_fd2);
            shm_unlink("map_fd1.txt");
            shm_unlink("map_fd2.txt");
            remove("map_fd1.txt");
            remove("map_fd2.txt");
            sem_destroy(input_semaphore);
            sem_destroy(output_semaphore);
            munmap(memptr_1,getpagesize());
            munmap(memptr_2,getpagesize());
            return 0;
        }
    }   
}