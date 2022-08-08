#include <memory>
#ifndef INC_5_LAB__TITERATOR_H_
#define INC_5_LAB__TITERATOR_H_
template <class node, class T> class Titerator {
public:
  Titerator(std::shared_ptr<node> n) { node_ptr = n; }
  std::shared_ptr<T> operator*() { return node_ptr->hexagon; }
  std::shared_ptr<T> operator->() { return node_ptr->next; }
  void operator++() { node_ptr = node_ptr->next; }
  Titerator operator++(int) {
    Titerator other(*this);
    ++(*this);
    return other;
  }
  bool operator==(Titerator const &i) { return node_ptr == i.node_ptr; };
  bool operator!=(Titerator const &i) { return !(*this == i); };

private:
  std::shared_ptr<node> node_ptr;
};

#endif // INC_5_LAB__TITERATOR_H_