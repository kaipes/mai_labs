#include <iostream>
#include "hexagon.h"
#include <cmath>

Hexagon::Hexagon(): a(0,0),b(0,0),c(0,0),d(0,0),e(0,0),f(0,0) {
} 
Hexagon::Hexagon(std::istream &is) {
    is >> a; 
    is >> b;
    is >> c;
    is >> d;
    is >> e;
    is >> f;
}
Hexagon::Hexagon(Point a1, Point b1,Point c1, Point d1, Point e1, Point f1): a(a1),b(b1),c(c1),d(d1),e(e1),f(f1) {
}
double Hexagon::Area() {
    return 0.5*abs(a.x()*b.y()+b.x()*c.y()+c.x()*d.y()+d.x()*e.y()+e.x()*f.y()+f.x()*a.y()-b.x()*a.y()-c.x()*b.y()-d.x()*c.y()-e.x()*d.y()-f.x()*e.y()-a.x()*f.y());
}
Hexagon::~Hexagon() {
}
size_t Hexagon::VertexesNumber() {
    return 6;
}
Hexagon::Hexagon(Hexagon& other):Hexagon(other.a,other.b,other.c,other.d,other.e,other.f) {
} 
Hexagon& Hexagon::operator = (const Hexagon& other) {
  if (this == &other) return *this;
  a = other.a;
  b = other.b;
  c = other.c;
  d = other.d;
  e = other.e;
  f = other.f;
  //std::cout << "Hexagon copied" << std::endl;
  return *this;
} 
Hexagon& Hexagon::operator == (const Hexagon& other) {
  if (this == &other){
    std::cout << "Hexagons are equal" << std::endl;
  } else {
    std::cout << "Hexagons are not equal" << std::endl;
  } 
} 
std::ostream& operator<<(std::ostream& os, Hexagon& h) {
  os << h.a << h.b << h.c << h.d << h.e << h.f;
  return os;
}
