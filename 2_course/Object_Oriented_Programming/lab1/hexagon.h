#ifndef HEXAGON_H
#define HEXAGON_H
#include "figure.h"
#include <iostream>

class Hexagon : public Figure {
    public:
    Hexagon(std::istream &is);

    virtual ~Hexagon();

    void Print(std::ostream &os);
    double Area();
    size_t VertexesNumber();

    private:
    Point a, b, c, d, e, f;
};

#endif // HEXAGON_H
