#include <iostream>
#include <algorithm>
#include <list>
#include <string>
using namespace std;

struct MemoryNode {
    char* begin;
    size_t capacity;
    string type;
};

ostream& operator << (ostream& os, const MemoryNode& node);
class BlocksAllocator {
public:

    explicit BlocksAllocator(size_t size_of_data);
    void* alloc(size_t memory_size);
    void dealloc(void* block);
    void print_memory(ostream& os) const;
    ~BlocksAllocator();
    
private:
    list<MemoryNode> mem_list;
    char* data;
};