#include "hexagon.h"
#include <cmath>
#include "point.h"

Hexagon::Hexagon(std::istream &is) {
    is >> a >> b >> c >> d >> e >> f;
}

void Hexagon::Print(std::ostream &os) {
    os << "Hexagon:" << a << b << c << d << e << f << std::endl;
}

double Hexagon::Area() {
    return 0.5*abs(a.x()*b.y()+b.x()*c.y()+c.x()*d.y()+d.x()*e.y()+e.x()*f.y()+f.x()*a.y()-b.x()*a.y()-c.x()*b.y()-d.x()*c.y()-e.x()*d.y()-f.x()*e.y()-a.x()*f.y());
}
size_t Hexagon::VertexesNumber(){
    return 6;
}
Hexagon::~Hexagon() {
    std::cout << "Hexagon deleted" << std::endl;
}
