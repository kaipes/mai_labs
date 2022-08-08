#include "BlocksAllocator.h"
using namespace std;

BlocksAllocator::BlocksAllocator(size_t size_of_data) {
    data = (char *)malloc(size_of_data);
    mem_list.push_front({data, size_of_data, "Freely"});
}

void *BlocksAllocator::alloc(size_t memory_size) {
    if (memory_size == 0) {
        return nullptr;
    }
    size_t size_of_node = 0;
    auto needed_node = mem_list.end();
    for (auto it = mem_list.begin(); it != mem_list.end(); ++it) {
        if (it->type == "Freely" && it->capacity >= memory_size) {
            size_of_node = it->capacity;
            needed_node = it;
        }
    }
    if (size_of_node == 0) {
        throw std::bad_alloc();
    }
    if (memory_size == size_of_node) {
        needed_node->type = "Occupied";
    } else {
        MemoryNode new_node{needed_node->begin + memory_size, needed_node->capacity - memory_size, "Freely"};
        needed_node->capacity = memory_size;
        needed_node->type = "Occupied";
        mem_list.insert(next(needed_node), new_node);
    }
    return (void *)(needed_node->begin);
}

void BlocksAllocator::dealloc(void *block) {
    auto it = find_if(mem_list.begin(), mem_list.end(), [block](const MemoryNode &node) {
        return node.begin == (char *) block && node.type == "Occupied";
    });
    if (it == mem_list.end()) {
        cerr << "This pointer wasnt allocated by this allocator";
    }
    it->type = "Freely";
    if (it != mem_list.begin() && prev(it)->type == "Freely") {
        auto prev_it = prev(it);
        prev_it->capacity += it->capacity;
        mem_list.erase(it);
        it = prev_it;
    }
    if (next(it) != mem_list.end() && next(it)->type == "Freely") {
        auto next_it = next(it);
        it->capacity += next_it->capacity;
        mem_list.erase(next_it);
    }
}

void BlocksAllocator::print_memory(ostream& os) const {
    int occ_sum = 0, free_sum = 0;
    for (auto& elem : mem_list) {
        os << elem << endl;
        if (elem.type == "Freely") {
            free_sum += elem.capacity;
        } else {
            occ_sum += elem.capacity;
        }
    }
    os << "Occupied memory " << occ_sum << endl;
    os << "Free memory " << free_sum << endl;

}

std::ostream& operator << (std::ostream& os, const MemoryNode& node) {
    if ("Freely" == node.type) {
        return os << "Node: capacity " << node.capacity << ", type " << "Freely";
    } else {
        return os << "Node: capacity " << node.capacity << ", type " << "Occupied";
    }
}

BlocksAllocator::~BlocksAllocator() {
    free(data);
}