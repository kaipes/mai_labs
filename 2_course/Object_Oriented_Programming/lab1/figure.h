#ifndef FIGURE_H
#define FIGURE_H
#include "point.h"
class Figure {
public:
    virtual void Print(std::ostream &os) = 0;
    virtual double Area() = 0;
    virtual size_t VertexesNumber() = 0;
    virtual ~Figure() {};
};

#endif // FIGURE_H