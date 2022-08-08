#include "triangle.h"
#include <cmath>

Triangle::Triangle(std::istream &is) {
    is >> a >> b >> c;
}

void Triangle::Print(std::ostream &os) {
    os << "Triangle:" << a << b << c << std::endl;
}

double Triangle::Area() {
    return 0.5*abs((b.x()-a.x())*(c.y()-a.y())-(c.x()-a.x()*(b.y()-a.y())));
}
size_t Triangle::VertexesNumber(){
    return 3;
}
Triangle::~Triangle() {
    std::cout << "Triangle deleted" << std::endl;
}