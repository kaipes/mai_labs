#include "octagon.h"
#include <cmath>

Octagon::Octagon(std::istream &is) {
    is >> a >> b >> c >> d >> e >> f >> g >> h;
}

void Octagon::Print(std::ostream &os) {
    os << "Octagon:" << a << b << c << d << e << f << g << h << std::endl;
}

double Octagon::Area() {
    return 0.5*abs(a.x() * b.y() + b.x() * c.y() + c.x() * d.y() + d.x() * e.y() + e.x() * f.y() + f.x() * g.y() + g.x() * h.y() + h.x() * a.y() - b.x() * a.y() - c.x() * b.y() - d.x() * c.y() - e.x() * d.y() - f.x() * e.y() - g.x() * f.y() - h.x() * g.y() - a.x() * h.y());
}

size_t Octagon::VertexesNumber(){
    return 8;
}
Octagon::~Octagon() {
    std::cout << "Octagon deleted" << std::endl;
}