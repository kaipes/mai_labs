#ifndef HLISTITEM_H
#define HLISTITEM_H
#include <iostream>
#include "hexagon.h"
#include <memory>

template <class T> class HListItem {
public:
  HListItem(const std::shared_ptr<Hexagon> &hexagon);
  template <class A> friend std::ostream& operator<<(std::ostream& os, HListItem<A> &obj);
  ~HListItem();
  std::shared_ptr<T> hexagon;
  std::shared_ptr<HListItem<T>> next;
  std::shared_ptr<HListItem<T>> SetNext(std::shared_ptr<HListItem<T>> &next_);
  std::shared_ptr<HListItem<T>> GetNext();
  std::shared_ptr<T>& GetValue();
};
#include "hlist_item.inl"
#endif //HLISTITEM_H