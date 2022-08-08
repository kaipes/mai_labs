#include <iostream>
#include "tlinkedlist.h"

template <class T>
Titerator<HListItem<T>, T> TLinkedList<T>::begin() {
  return Titerator<HListItem<T>, T> (front);
}

template <class T>
Titerator<HListItem<T>, T> TLinkedList<T>::end() {
  return Titerator<HListItem<T>, T>(nullptr);
}

template <class T> TLinkedList<T>::TLinkedList() {
  size_of_list = 0;
  std::shared_ptr<HListItem<T>> front = nullptr;
  std::shared_ptr<HListItem<T>> back = nullptr;
  std::cout << "Hexagon List created" << std::endl; 
}
template <class T> TLinkedList<T>::TLinkedList(const std::shared_ptr<TLinkedList> &other){
  front = other->front;
  back = other->back;
}
template <class T> size_t TLinkedList<T>::Length() {
  return size_of_list;
}
template <class T> bool TLinkedList<T>::Empty() {
  return size_of_list;
}
template <class T> Hexagon& TLinkedList<T>::GetItem(size_t idx){
  int k = 0;
  std::shared_ptr<HListItem<T>> obj = front;
  while (k != idx){
    k++;
    obj = obj->next;
  }
  return *obj->hexagon;
}
template <class T> Hexagon& TLinkedList<T>::First() {
    return *front->hexagon;
}
template <class T> Hexagon& TLinkedList<T>::Last() {
  std::shared_ptr<HListItem<T>> node = this->front;
    while(node->next != nullptr) {
        node = node->next;
    }
    return *node->hexagon;
}
template <class T> void TLinkedList<T>::InsertLast( std::shared_ptr<Hexagon> &&hexagon) {
  std::shared_ptr<HListItem<T>> obj (new HListItem<T>(hexagon));
 // std::shared_ptr<HListItem<T>> obj = std::make_shared<HListItem<T>>(HListItem<T>(hexagon));
  if(size_of_list == 0) {
    front = obj;
    front->next = nullptr;
    size_of_list++;
    return;
  }
  std::shared_ptr<HListItem<T>> end = this->front;
  while(end->next != nullptr) {
    end = end->next;
  }
  end->next = obj;
  obj->next = nullptr;
  size_of_list++;
}
template <class T> void TLinkedList<T>::RemoveLast() {
  if (size_of_list == 0) {
    std::cout << "Hexagon does not pop_back, because the Hexagon List is empty" << std:: endl;
  } else {
    if (size_of_list == 1) {
      RemoveFirst();
      size_of_list--;
      return;
    }
    std::shared_ptr<HListItem<T>> prev_del = front;
    std::shared_ptr<HListItem<T>> save;
    while (prev_del->next != nullptr) {
      save = prev_del;
      prev_del = prev_del->next;
    }
    save->next = nullptr;
    prev_del->next = nullptr;
    size_of_list--;
    } 
}
template <class T> void TLinkedList<T>::InsertFirst( std::shared_ptr<Hexagon> &&hexagon) {
    std::shared_ptr<HListItem<T>> obj (new HListItem<T>(hexagon));
    if(size_of_list == 0) {
      front = obj;
    } else {
      obj->next = front;
      front = obj;
    }
    size_of_list++;
} 
template <class T> void TLinkedList<T>::RemoveFirst() {
    if (size_of_list == 0) {
      std::cout << "Hexagon does not pop_front, because the Hexagon List is empty" << std:: endl;
    } else {
    std::shared_ptr<HListItem<T>> del = front;
    front = del->next;
    size_of_list--;
    }
}
template <class T> void TLinkedList<T>::Insert(std::shared_ptr<Hexagon> &&hexagon,size_t position) {
  if (position <0) {
    std::cout << "Position < zero" << std::endl;
  } else if (position > size_of_list) {
    std::cout << " Position > size_of_list" << std::endl;
  } else {
    std::shared_ptr<HListItem<T>> obj (new HListItem<T>(hexagon));
    if (position == 0) {
      front = obj;
    } else {
      int k = 0;
      std::shared_ptr<HListItem<T>> prev_insert = front;
      std::shared_ptr<HListItem<T>> next_insert;
      while(k+1 != position) {
        k++;
        prev_insert = prev_insert->next;
      }
      next_insert = prev_insert->next;
      prev_insert->next = obj; // = obj;
      obj->next = next_insert; // = next_insert;
    }
    size_of_list++;
  }
}
template <class T> void TLinkedList<T>::Remove(size_t position) {
  if (position > size_of_list ) {
    std:: cout << "Position " << position << " > " << "size " << size_of_list << " Not correct erase" << std::endl;
  } else if (position < 0) {
    std::cout << "Position < 0" << std::endl;
  } else {
    if (position == 0) {
      RemoveFirst();
    } else {
      int k = 0;
      std::shared_ptr<HListItem<T>> prev_erase = front;
      std::shared_ptr<HListItem<T>> next_erase;
      std::shared_ptr<HListItem<T>> del;
      while( k+1 != position) {
        k++;
        prev_erase = prev_erase->next;
      }
      next_erase = prev_erase->next;
      del = prev_erase->next;
      next_erase = del->next;
      prev_erase->next = next_erase; // = next_erase;
    }
    size_of_list--;
  }
}
template <class T> void TLinkedList<T>::Clear() {
  std::shared_ptr<HListItem<T>> del = front;
  std::shared_ptr<HListItem<T>> prev_del;
  if(size_of_list !=0 ) {
    while(del->next != nullptr) {
      prev_del = del;
      del = del->next;
    }
    size_of_list = 0;
    //   std::cout << "HListItem deleted" << std::endl;
  } 
  size_of_list = 0;
  std::shared_ptr<HListItem<T>> front;
  std::shared_ptr<HListItem<T>> back;
}
template <class T> std::ostream& operator<<(std::ostream& os,const TLinkedList<T>& hl) {
  if (hl.size_of_list == 0) {
    os << "The hexagon list is empty, so there is nothing to output" << std::endl;
  } else {
    os << "Print Hexagon List" << std::endl;
    std::shared_ptr<HListItem<T>> obj = hl.front;
    for(int i = 0; i < hl.size_of_list - 1; i++)
    {
        os << *obj->hexagon << " " << "," << " ";
        obj = obj->next;
    }
    os << *obj->hexagon;
    os << std::endl;
    }
    return os;
}
template <class T> TLinkedList<T>::~TLinkedList() {
}
