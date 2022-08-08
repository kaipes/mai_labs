#ifndef HEXAGON_H
#define HEXAGON_H
#include <iostream>
#include "figure.h"
#include "point.h"
#include <memory>

class Hexagon : public Figure {
public:
    Hexagon();
    Hexagon(std::istream &is);
    Hexagon(Point a, Point b, Point c, Point d, Point e, Point f);
    Hexagon(std::shared_ptr<Hexagon>& other);
    double Area();
    size_t VertexesNumber();
    virtual ~Hexagon();
    Hexagon& operator=(const Hexagon& other);
    Hexagon& operator==(const Hexagon& other);
    friend std::ostream& operator<<(std::ostream& os, Hexagon& h);
private:
    Point a, b, c, d, e, f;
};

#endif // HEXAGON_H