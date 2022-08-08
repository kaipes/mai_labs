#include <iostream>
#include "hexagon.h"
#include "octagon.h"
#include "triangle.h"
using namespace std;

int main() {
    Hexagon a(std::cin);
    std::cout << "Square = " << a.Area() << std::endl;
    a.Print(std::cout);

    Octagon b(std::cin);
    std::cout << "Square = " << a.Area() << std::endl;
    b.Print(std::cout);

    Triangle c(std::cin);
    std::cout << "Square = " << c.Area() << std::endl;
    c.Print(std::cout);
}