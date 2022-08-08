#include <iostream>
#include "BitString.h"
#include <cmath>
using namespace std;

BitString operator "" _bit(const char* str, size_t size) {
    int cnt = 0;
    unsigned long long one=0;
    unsigned long long two = 0;
    while (str[cnt]!=' ') {
        one*=10;
        one+=str[cnt]-'0';
        cnt++;
    }
    cnt++;
    while (str[cnt]!='\0') {
        two*=10;
        two+=str[cnt]-'0';
        cnt++;
    }
    BitString a(one,two);
    return a;
}
int main() {
    BitString a(23425, 32413);
    BitString b(678686, 345346);
    //BitString c(cin);
    cout << "BitString a:" << endl << a << endl;
    cout << "BitString b:" << endl << b << endl;
    cout << "AND" << endl << (a&b) << endl;
    cout << "OR" << endl << (a||b) << endl;
    cout << "XOR" << endl << (a^b) << endl;
    cout << "NOT" << endl << ~a << endl;
    cout << "1 in a" << endl << a.count() << endl;
    cout << (b > a) << endl;
    cout << a.include(b) << endl;
    cout << "Example with literal:" << "2342235 423523"_bit << endl;
    BitString test(2342235,423523);
     cout << "Example with literal:" << test << endl;
}