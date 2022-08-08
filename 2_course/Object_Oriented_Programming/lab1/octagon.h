#ifndef OCTAGON_H
#define OCTAGON_H
#include "figure.h"
#include <iostream>

class Octagon : public Figure {
    public:
    Octagon(std::istream &is);

    virtual ~Octagon();

    void Print(std::ostream &os);
    double Area();
    size_t VertexesNumber();

    private:
    Point a, b, c, d, e, f, g, h;
};

#endif // ОСТAGON_H