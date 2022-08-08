#ifndef VECTOR_ITEM_H
#define VECTOR_ITEM_H

#include <memory>

template<typename T> 
class Vector_item {
    public:
        Vector_item(): data(0) {};
        Vector_item(T t): data(t){};
        std::shared_ptr<Vector_item<T>> Get_next(){
            return next;
        };
        void Set_next(std::shared_ptr<Vector_item<T>> next_){
            next = next_;
        };
        T Get_data(){
            return data;
        }
    private:
        std::shared_ptr<Vector_item<T>> next = nullptr;
        T data;
};

#endif