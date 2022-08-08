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
  bool Empty();
  Hexagon& First();
  Hexagon& Last();
  TLinkedList(const TLinkedList& other);
  Hexagon& GetItem(size_t idx);
  void InsertFirst(const Hexagon &&hexagon);
  void InsertLast(const Hexagon &&hexagon);
  void RemoveLast();
  void RemoveFirst();
  void Insert(const Hexagon &&hexagon, size_t position);
  void Remove(size_t position);
  void Clear();
  friend std::ostream& operator<<(std::ostream& os, TLinkedList& list);
  ~TLinkedList(); 
private:
  HListItem *front;
  HListItem *back;
};
 
#endif // HList_H
