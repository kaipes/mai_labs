#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "figure.h"
#include <iostream>

class Triangle : public Figure {
    public:
    Triangle(std::istream &is);

    virtual ~Triangle();

    void Print(std::ostream &os);
    double Area();
    size_t VertexesNumber();

    private:
    Point a, b, c, d, e, f, g, h;
};

#endif // Triangle_H