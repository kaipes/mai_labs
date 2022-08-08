#include <iostream>
#include "hexagon.h"
#include <memory>

class HListItem {
public:
  HListItem(const std::shared_ptr<Hexagon> &hexagon);
  friend std::ostream& operator<<(std::ostream& os, std::shared_ptr<HListItem>&& obj);
  ~HListItem();
  std::shared_ptr<Hexagon> hexagon;
  std::shared_ptr<HListItem> next;
};
 
