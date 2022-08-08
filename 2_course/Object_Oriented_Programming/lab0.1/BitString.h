#ifndef BITSTRING_H
#define BITSTRING_H
#include <iostream>

class BitString {
    public:
    BitString();
    BitString(std::istream &is);
    BitString(unsigned long long a, unsigned long long b);
    BitString(const BitString &other);
    unsigned long long get_one();
    unsigned long long get_two();
    friend std::ostream& operator<<(std::ostream& os,const BitString& a);
    int count();
    BitString shiftLeft(int n);
    BitString shiftRight(int n);
    bool include(BitString& other);
    bool operator <(BitString& other);
    bool operator >(BitString& other);
    bool operator ==(BitString& other); 
    BitString operator &( BitString &other);
    BitString operator ||(BitString &other);
    BitString operator ^(BitString &other);
    BitString operator ~();
    BitString operator >>(int n) const;
    BitString operator<<(int n) const;
    private:
    unsigned long long one_, two_;
};

#endif // BITSTRING_H