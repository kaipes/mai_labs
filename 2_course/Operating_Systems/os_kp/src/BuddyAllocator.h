#include <exception>
#include <map>
#include <iostream>
using namespace std;

class BuddyAllocator {
public:

    using MapType = multimap<size_t, char*>;
    BuddyAllocator(size_t minBlockSizeArg, size_t maxSizeArg);
    void* alloc(const size_t size);
    void dealloc(void* ptr, size_t size);
    void print_memory(ostream& os) const;
    ~BuddyAllocator();

private:

    size_t Rounder(const size_t size);
    size_t minBlockSize, maxSize;
    MapType allocMap;
    char *allocatedBlocks;

};

