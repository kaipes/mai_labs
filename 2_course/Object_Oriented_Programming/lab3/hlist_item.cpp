#include <iostream>
#include "hlist_item.h"

HListItem::HListItem(const std::shared_ptr<Hexagon> &hexagon) {
  this->hexagon = hexagon;
  this->next = nullptr;
}
std::ostream& operator<<(std::ostream& os,std::shared_ptr<HListItem>& obj) {
  os << "[" << obj->hexagon << "]" << std::endl;
  return os;
}
HListItem::~HListItem() {
}

