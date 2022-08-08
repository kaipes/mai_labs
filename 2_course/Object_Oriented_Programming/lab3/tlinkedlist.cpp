#include <iostream>
#include "tlinkedlist.h"
 
TLinkedList::TLinkedList() {
  size_of_list = 0;
  std::shared_ptr<HListItem> front;
  std::shared_ptr<HListItem> back;
  std::cout << "Hexagon List created" << std::endl; 
}
TLinkedList::TLinkedList(const std::shared_ptr<TLinkedList> &other){
  front = other->front;
  back = other->back;
}
size_t TLinkedList::Length() {
  return size_of_list;
}
bool TLinkedList::Empty() {
  return size_of_list;
}
std::shared_ptr<Hexagon>& TLinkedList::GetItem(size_t idx){
  int k = 0;
  std::shared_ptr<HListItem> obj = front;
  while (k != idx){
    k++;
    obj = obj->next;
  }
  return obj->hexagon;
}
std::shared_ptr<Hexagon>& TLinkedList::First() {
  return front->hexagon;
}
std::shared_ptr<Hexagon>& TLinkedList::Last() {
  return back->hexagon;
}
void TLinkedList::InsertLast(const std::shared_ptr<Hexagon> &&hexagon) {
  std::shared_ptr<HListItem> obj (new HListItem(hexagon));
  if(size_of_list == 0) {
    front = obj;
    back = obj;
    size_of_list++;
    return;
  }
  back->next = obj;
  back = obj;
  obj->next = nullptr;
  size_of_list++;
}
void TLinkedList::RemoveLast() {
  if (size_of_list == 0) {
    std::cout << "Hexagon does not pop_back, because the Hexagon List is empty" << std:: endl;
  } else {
    if (front == back) {
      RemoveFirst();
      size_of_list--;
      return;
    }
    std::shared_ptr<HListItem> prev_del = front;
    while (prev_del->next != back) {
      prev_del = prev_del->next;
    }
    prev_del->next = nullptr;
    back = prev_del;
    size_of_list--;
    } 
}
void TLinkedList::InsertFirst(const std::shared_ptr<Hexagon> &&hexagon) {
    std::shared_ptr<HListItem> obj(new HListItem(hexagon));
    if(size_of_list == 0) {
      front = obj;
      back = obj;
    } else {
      obj->next = front;
      front = obj;
    }
    size_of_list++;
}
void TLinkedList::RemoveFirst() {
    if (size_of_list == 0) {
      std::cout << "Hexagon does not pop_front, because the Hexagon List is empty" << std:: endl;
    } else {
    std::shared_ptr<HListItem> del = front;
    front = del->next;
    size_of_list--;
    }
}
void TLinkedList::Insert(const std::shared_ptr<Hexagon> &&hexagon,size_t position) {
  if (position <0) {
    std::cout << "Position < zero" << std::endl;
  } else if (position > size_of_list) {
    std::cout << " Position > size_of_list" << std::endl;
  } else {
    std::shared_ptr<HListItem> obj (new HListItem(hexagon));
    if (position == 0) {
      front = obj;
      back = obj;
    } else {
      int k = 0;
      std::shared_ptr<HListItem> prev_insert = front;
      std::shared_ptr<HListItem> next_insert;
      while(k+1 != position) {
        k++;
        prev_insert = prev_insert->next;
      }
      next_insert = prev_insert->next;
      prev_insert->next = obj;
      obj->next = next_insert;
    }
    size_of_list++;
  }
}
void TLinkedList::Remove(size_t position) {
  if (position > size_of_list ) {
    std:: cout << "Position " << position << " > " << "size " << size_of_list << " Not correct erase" << std::endl;
  } else if (position < 0) {
    std::cout << "Position < 0" << std::endl;
  } else {
    if (position == 0) {
      RemoveFirst();
    } else {
      int k = 0;
      std::shared_ptr<HListItem> prev_erase = front;
      std::shared_ptr<HListItem> next_erase;
      std::shared_ptr<HListItem> del;
      while( k+1 != position) {
        k++;
        prev_erase = prev_erase->next;
      }
      next_erase = prev_erase->next;
      del = prev_erase->next;
      next_erase = del->next;
      prev_erase->next = next_erase;
    }
    size_of_list--;
  }
}
void TLinkedList::Clear() {
  std::shared_ptr<HListItem> del = front;
  std::shared_ptr<HListItem> prev_del;
  if(size_of_list !=0 ) {
    while(del->next != nullptr) {
      prev_del = del;
      del = del->next;
    }
    size_of_list = 0;
    //   std::cout << "HListItem deleted" << std::endl;
  } 
  size_of_list = 0;
  std::shared_ptr<HListItem>* front;
  std::shared_ptr<HListItem> back;
}
std::ostream& operator<<(std::ostream& os, TLinkedList& hl) {
  if (hl.size_of_list == 0) {
    os << "The hexagon list is empty, so there is nothing to output" << std::endl;
  } else {
    os << "Print Hexagon List" << std::endl;
    std::shared_ptr<HListItem> obj = hl.front;
    while(obj != nullptr) {
      if (obj->next != nullptr) {
        os << obj->hexagon << " " << "," << " ";
        obj = obj->next;
      } else {
        os << obj->hexagon;
        obj = obj->next;
      }
    }
    os << std::endl;
  }
  return os;
}
TLinkedList::~TLinkedList() {
  std::shared_ptr<HListItem> del = front;
  std::shared_ptr<HListItem> prev_del;
  if(size_of_list !=0 ) {
    while(del->next != nullptr) {
      prev_del = del;
      del = del->next;
    }
    size_of_list = 0;
    std::cout << "Hexagon List deleted" << std::endl;
  } 
}
