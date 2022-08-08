#include <iostream>
#include "BuddyAllocator.h"
#include <chrono>
#include "BlocksAllocator.h"
#include <vector>
using namespace std;
int main() {
    using namespace std::chrono;
    {
        steady_clock::time_point list_allocator_init_start = steady_clock::now();
        BlocksAllocator list_allocator(4096);
        steady_clock::time_point list_allocator_init_end = steady_clock::now();
        cerr << "List allocator initialization with one page of memory :"
                  << chrono::duration_cast<std::chrono::nanoseconds>(
                          list_allocator_init_end - list_allocator_init_start).count()
                  << " ns" << endl;


        steady_clock::time_point buddy_allocator_init_start = steady_clock::now();
        BuddyAllocator bAlloc(32, 4096);
        steady_clock::time_point buddy_allocator_init_end = steady_clock::now();
        cerr << "Buddy allocator initialization with one page of memory :"
                  << chrono::duration_cast<std::chrono::nanoseconds>(
                  buddy_allocator_init_end - buddy_allocator_init_start).count()
                  << " ns" << endl;
        cerr << endl;
    }
    cerr << "First test: Allocate 10 char[256] arrays, free 5 of them, allocate 10 char[128] arrays:" << endl;
    {
        BlocksAllocator allocator(4096);
        vector<char *> pointers(15, nullptr);
        steady_clock::time_point test1_start = steady_clock::now();
        for (int i = 0; i < 10; ++i) {
            pointers[i] = (char *) allocator.alloc(256);
        }
        for (int i = 5; i < 10; ++i) {
            allocator.dealloc(pointers[i]);
        }
        for (int i = 5; i < 15; ++i) {
            pointers[i] = (char *) allocator.alloc(128);
        }
        steady_clock::time_point test1_end = steady_clock::now();
        cerr << "List allocator first test: "
             << std::chrono::duration_cast<chrono::microseconds>(test1_end - test1_start).count()
             << " microseconds" << endl;
        allocator.print_memory(cerr);
        for (int i = 0; i < 15; ++i) {
            allocator.dealloc(pointers[i]);
        }
    }
    {
        BuddyAllocator bAlloc(16, 4096);
        vector<char *> pointer(15, nullptr);
        steady_clock::time_point buddy_test1_start = steady_clock::now();
        for (int i = 0; i < 10; ++i) {
            pointer[i] = (char *) bAlloc.alloc(256);
        }
        for (int i = 5; i < 10; ++i) {
            bAlloc.dealloc(pointer[i], 256);
        }
        for (int i = 5; i < 15; ++i) {
            pointer[i] = (char *) bAlloc.alloc(128);
        }
        steady_clock::time_point buddy_test1_end = steady_clock::now();
        cerr << "Buddy allocator first test: "
                 << chrono::duration_cast<std::chrono::microseconds>(buddy_test1_end - buddy_test1_start).count()
                 << " microseconds" << std::endl;
        for (int i = 0; i < 5; ++i) {
            bAlloc.dealloc(pointer[i], 256);
        }
        bAlloc.print_memory(cerr);
        for (int i = 5; i<15; ++i) {
            bAlloc.dealloc(pointer[i], 128);
        }
    }
    cerr << "Second test: Allocate and free 750 20 bytes arrays:\n";
    {
        BlocksAllocator allocator(16000);
        std::vector<char *> pointers(900, nullptr);
        int arr_size = 10;
        steady_clock::time_point alloc_start = steady_clock::now();
        for (int i = 0; i < 900; ++i) {
            pointers[i] = (char *) allocator.alloc(arr_size);
        }
        steady_clock::time_point alloc_end = steady_clock::now();
        for (int i = 0; i < 900; ++i) {
            allocator.dealloc(pointers[i]);
        }
        cerr << "List allocator second test:" << endl
                  << "Allocation: " << duration_cast<chrono::microseconds>(alloc_end - alloc_start).count()
                  << " microseconds" << endl << endl;
    }
    {
        BuddyAllocator allocator(2, 16000);
        vector<char *> pointers(900, nullptr);
        steady_clock::time_point alloc_start = steady_clock::now();
        int arr_size = 10;
        for (int i = 0; i < 900; ++i) {
            pointers[i] = (char *) allocator.alloc(arr_size);
        }
        steady_clock::time_point alloc_end = steady_clock::now();
        for (int i = 0; i < 900; ++i) {
            allocator.dealloc(pointers[i], arr_size);
        }
        steady_clock::time_point test_end = steady_clock::now();
        cerr << "Buddy allocator second test:" << endl
                  << "Allocation :" << duration_cast<chrono::microseconds>(alloc_end - alloc_start).count()
                  << " microseconds" << endl;
    }
}
