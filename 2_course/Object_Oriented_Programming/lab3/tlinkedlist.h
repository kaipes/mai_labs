#ifndef HLIST_H
#define HLIST_H
#include <iostream>
#include "hlist_item.h"
#include "hexagon.h"

class TLinkedList {
public:
  TLinkedList();
  int size_of_list;
  size_t Length();
  std::shared_ptr<Hexagon>& First();
  std::shared_ptr<Hexagon>& Last();
  std::shared_ptr<Hexagon>& GetItem(size_t idx);
  bool Empty();
  TLinkedList(const std::shared_ptr<TLinkedList> &other);
  void InsertFirst(const std::shared_ptr<Hexagon> &&hexagon);
  void InsertLast(const std::shared_ptr<Hexagon> &&hexagon);
  void RemoveLast();
  void RemoveFirst();
  void Insert(const std::shared_ptr<Hexagon> &&hexagon, size_t position);
  void Remove(size_t position);
  void Clear();
  friend std::ostream& operator<<(std::ostream& os, TLinkedList& list);
  ~TLinkedList(); 
private:
  std::shared_ptr<HListItem> front;
  std::shared_ptr<HListItem> back;
};
 
#endif // HList_H


