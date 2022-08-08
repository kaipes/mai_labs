#include <iostream>
#include "BitString.h"
#include <cmath>
using namespace std;
int main() {
    BitString a(23425, 32413);
    BitString b(cin);
    BitString c(678686, 345346);
    cout << "BitString a:" << endl << a << endl;
    cout << "BitString b:" << endl << b << endl;
    cout << "AND" << endl << (a&b) << endl;
    cout << "OR" << endl << (a||b) << endl;
    cout << "XOR" << endl << (a^b) << endl;
    cout << "NOT" << endl << ~a << endl;
    cout << "1 in a" << endl << a.count() << endl;
    cout << (b > a) << endl;
    cout << b.include(c) << endl;
}