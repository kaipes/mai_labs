#include <iostream>
#include "tlinkedlist.h"

int main() {
  TLinkedList tlinkedlist;
  tlinkedlist.Empty();
  tlinkedlist.InsertLast(std::shared_ptr<Hexagon>(new Hexagon(Point(1,2),Point(2,3),Point(3,4),Point(5,6),Point(7,8),Point(9,10))));
  tlinkedlist.InsertLast(std::shared_ptr<Hexagon>(new Hexagon(Point(11,12),Point(12,13),Point(13,14),Point(14,15),Point(15,16),Point(16,17))));
  tlinkedlist.InsertLast(std::shared_ptr<Hexagon>(new Hexagon(Point(17,18),Point(18,19),Point(19,20),Point(20,21),Point(21,22),Point(23,24))));
  tlinkedlist.InsertLast(std::shared_ptr<Hexagon>(new Hexagon(Point(17,18),Point(18,19),Point(19,20),Point(20,21),Point(21,22),Point(23,24))));
  std::cout << tlinkedlist;
  tlinkedlist.RemoveLast();
  std::cout << tlinkedlist.Length() << std::endl;
  tlinkedlist.RemoveFirst();
  tlinkedlist.InsertFirst(std::shared_ptr<Hexagon>(new Hexagon(Point(2,3),Point(3,4),Point(4,5),Point(5,6),Point(6,7),Point(7,8))));
  tlinkedlist.Insert(std::shared_ptr<Hexagon>(new Hexagon(Point(1,1),Point(2,3),Point(3,4),Point(5,6),Point(7,8),Point(9,16))),2);
  std::cout << tlinkedlist.Empty() << std::endl;
  std::cout << tlinkedlist.First() << std::endl;
  std::cout << tlinkedlist.Last() << std::endl;
  std::cout << tlinkedlist.GetItem(2) << std::endl;
  tlinkedlist.Remove(2);
  std::cout << tlinkedlist;
  tlinkedlist.Clear();
  return 0;
}
