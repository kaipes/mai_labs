#include "tallocation_block.h"
#include <iostream>

TAllocationBlock::TAllocationBlock(size_t size, size_t count)
        : _size(size), _count(count) {
    _used_blocks = (char *) malloc(_size * _count);
    for (size_t i = 0; i < _count; ++i) {
        vec_free_blocks.push_back(_used_blocks + i * _size);
        std::cout << i << " OK" << std::endl;
    }
    _free_count = _count;
    std::cout << "TAllocationBlock: Memory init" << std::endl;
}

void *TAllocationBlock::allocate() {
    void *result = nullptr;

    if (_free_count > 0) {
        std::cout << vec_free_blocks.size() << std::endl;
        result = vec_free_blocks.back();
        vec_free_blocks.pop();
        _free_count--;
        std::cout << "TAllocationBlock: Allocate " << (_count - _free_count);
        std::cout << " of " << _count << std::endl;

    } else {
        std::cout << "TAllocationBlock: No memory exception :-)" << std::endl;
    }

    return result;
}

void TAllocationBlock::deallocate(void *pointer) {
    std::cout << "TAllocationBlock: Deallocate block " << std::endl;

    vec_free_blocks[_free_count] = pointer;
    _free_count++;
}

bool TAllocationBlock::has_free_blocks() {
    return _free_count > 0;
}

TAllocationBlock::~TAllocationBlock() {
    if (_free_count < _count) {
        std::cout << "TAllocationBlock: Memory leak?" << std::endl;
    } else {
        std::cout << "TAllocationBlock: Memory freed" << std::endl;
    }
    delete _used_blocks;
}