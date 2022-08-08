#include <iostream>
#include "hexagon.h"


class HListItem {
public:
  HListItem(const Hexagon &hexagon);
  friend std::ostream& operator<<(std::ostream& os, HListItem& obj);
  ~HListItem();
  Hexagon hexagon;
  HListItem* next;
};
 
