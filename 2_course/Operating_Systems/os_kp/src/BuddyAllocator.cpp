#include "BuddyAllocator.h"
using MapType = multimap<size_t, char*>;
BuddyAllocator::BuddyAllocator(size_t minBlockSizeArg, size_t maxSizeArg):minBlockSize(minBlockSizeArg),maxSize(maxSizeArg) {
    allocatedBlocks = static_cast<char*>(::operator new(maxSize));
    allocMap.insert({maxSize, allocatedBlocks});
}

void *BuddyAllocator::alloc(const size_t size) {

    if (size == 0) {
        return nullptr;
    }
    size_t roundUp = Rounder(size);

    for (MapType::iterator it = allocMap.begin(); it != allocMap.end(); ++it) {
        if (it->first == size) { // Found the block of appropriate size
            void* result {
                it->second
            };
            allocMap.erase(it);
            return result;
        } else if (it->first > size) { // Map stores block sizes in ascending order
            int allocSize = it->first;
            char *blockStart = it->second;

            while (allocSize > size) {
                allocSize /= 2;
                if (allocSize < size) { 
                    break; 
                }
                allocMap.insert(pair<size_t, char*> (allocSize, blockStart + allocSize));
            }
            allocMap.erase(it);
            return blockStart;
        }
    }
    throw std::bad_alloc();
}

void BuddyAllocator::dealloc(void* ptr, size_t size) {
    size_t bufferedSize = size;
    while(true) {
        pair<MapType::iterator, MapType::iterator> range (allocMap.equal_range(bufferedSize));
        if (range.first != allocMap.end() && range.first->first == bufferedSize) { // Free blocks of same size found
            auto it = range.first;
            short index = ((char*)ptr - allocatedBlocks) / bufferedSize % 2;
            // If index is 1 then element is odd, else even

            while (it != range.second) {
                    // If difference between the two pointers equals to size,
                    // then we can merge them into one, since they are both free
                if (index == 1) {
                    if (((char*)ptr - it->second) == bufferedSize) {
                        bufferedSize *= 2;
                        ptr = it->second;
                        allocMap.erase(it);
                        break; // Element found, break of while loop
                    }
                } else {
                    if ((it->second - (char*)ptr) == bufferedSize) {
                        bufferedSize *= 2;
                        allocMap.erase(it);
                        break; // Element found, break of while loop
                    }
                }
                ++it;
            }
            if (it == range.second) { // No elements found in this size range
                allocMap.insert(std::pair<size_t, char*> (bufferedSize, (char*)ptr));
                break;
            } else {
                continue;
            }
        } // No elements of this size found; break out
        else {
            allocMap.insert(std::pair<size_t, char*> (bufferedSize, (char*)ptr));
            break;
        }
    }
    return;   
}

void BuddyAllocator::print_memory(ostream& os) const {
    int occ_mem = 0;
    for (auto& p: allocMap) {
        occ_mem += p.first;
    }
    int free_mem = maxSize - occ_mem;
    os << "Occupied memory " << occ_mem << "\n" << "Free memory " << free_mem  << "\n\n";
}

BuddyAllocator::~BuddyAllocator() {
    ::operator delete(allocatedBlocks);
    allocMap.clear();
}

size_t BuddyAllocator::Rounder(const size_t size) {
        if (size <= minBlockSize) return minBlockSize;

        size_t roundUp = 1;
        while (roundUp < size) { 
            roundUp <<= 1; 
        }
        return roundUp;
}

