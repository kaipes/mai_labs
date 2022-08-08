#include <iostream>
#include "hlist_item.h"

template <class T> HListItem<T>::HListItem(const std::shared_ptr<Hexagon> &hexagon) {
  this->hexagon = hexagon;
  this->next = nullptr;
}
template <class A> std::ostream& operator<<(std::ostream& os,HListItem<A> &obj) {
  os << "[" << obj.hexagon << "]" << std::endl;
  return os;
}
template <class T> HListItem<T>::~HListItem() {
}
