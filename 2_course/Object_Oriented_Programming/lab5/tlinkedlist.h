#ifndef HLIST_H
#define HLIST_H
#include <iostream>
#include "hlist_item.h"
#include "hexagon.h"
#include <memory>
#include "titerator.h"

template <class T> class TLinkedList {
public:
  TLinkedList();
  int size_of_list;
  size_t Length();
  Hexagon& First();
  Hexagon& Last();
  Hexagon& GetItem(size_t idx);
  bool Empty();
  TLinkedList(const std::shared_ptr<TLinkedList> &other);
  void InsertFirst(std::shared_ptr<Hexagon> &&hexagon);
  void InsertLast(std::shared_ptr<Hexagon> &&hexagon);
  void RemoveLast();
  void RemoveFirst();
  void Insert(std::shared_ptr<Hexagon> &&hexagon, size_t position);
  void Remove(size_t position);
  void Clear();
  template <class A> friend std::ostream& operator<<(std::ostream& os,const TLinkedList<A>& list);
  ~TLinkedList();
  Titerator<HListItem<T>, T> begin();
  Titerator<HListItem<T>, T> end();  
private:
  std::shared_ptr<HListItem<T>> front;
  std::shared_ptr<HListItem<T>> back;
};
#include "tlinkedlist.inl"
#endif //HList_H

