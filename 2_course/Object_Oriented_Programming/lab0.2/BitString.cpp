#include <iostream>
#include "BitString.h"
#include <cmath>
using namespace std;
BitString::BitString(){
    one_ = 0;
    two_ = 0;
};
BitString::BitString(std::istream &is) {
    is >> one_; 
    is >> two_;
};
BitString:: BitString(unsigned long long a, unsigned long long b) {
    one_ = a;
    two_ = b;
};
BitString::BitString(const BitString &other) {
    one_ = other.one_;
    two_ = other.two_; 
};
unsigned long long BitString::get_one() {
    return one_;
}
unsigned long long BitString::get_two() {
    return two_;
}
BitString BitString:: operator &( BitString &other)  {
    BitString a(one_ & other.one_, two_ & other.two_);
    return a;
}
BitString BitString:: operator ||(BitString &other) {
    BitString a(one_ | other.one_, two_ | other.two_);
    return a;
}
BitString BitString::operator ^(BitString &other) {
    BitString a(one_ ^ other.one_, two_ ^ other.two_);
    return a;
}
BitString BitString::operator ~() {
    BitString a(~one_,~two_);
    return a;
}
BitString BitString::operator >>(int n) const {
    if(n > 128) {
        return BitString(0,0);
    }
    BitString bs(*this);
    unsigned long long b = pow(2, 63);
    unsigned long long a = 1;
    for(int i = 0; i < n; ++i){
        bs.two_ >>= 1;
        if(bs.one_ & 1){
            bs.two_ |= b;
        }
        bs.one_ >>= 1;
    }
    return bs;
}
BitString BitString::operator<<(int n) const{
    if(n > 128) {
        return BitString(0,0);
    }
    BitString bs(*this);
    unsigned long long a = pow(2, 63);
    for(int i = 0; i < n; ++i){
        bs.one_ <<= 1;
        if(bs.two_ & a) {
            bs.one_ |= 1;
            }
        bs.two_ <<= 1;
        }
        return bs;
    }
std::ostream& operator<<(std::ostream& os,const BitString& bs){
    int i = 63;
    while (i >= 0) {
        os << ((bs.one_ >> i) & 1);
        i--;
    }
    i = 63;
    while (i >= 0) {
        os << ((bs.two_ >> i) & 1);
        i--;
    }
    return os;
}
BitString BitString::shiftLeft(int n) {
    if(n > 128) {
        return BitString(0,0);
    }
    for(int i = 0; i < n; ++i){
        this->one_ <<= 1;
        if(this->two_ & (unsigned long long)pow(2, 63)) {
            this->one_ |= 1;
            }
        this->two_ <<= 1;
    } 
    return *this;
}
BitString BitString::shiftRight(int n) {
     if(n > 128) {
        return BitString(0,0);
    }
    for(int i = 0; i < n; ++i){
        this->two_ >>= 1;
        if(this->one_ & 1){
            this->two_ |= (unsigned long long)pow(2, 63);
        }
        this->one_ >>= 1;
    }
    return *this;
}
int BitString::count() {
    int i = 63;
    int cnt = 0;
    while (i >= 0) {
        if ((one_ >> i) & 1) {
            cnt++;
        }
        i--;
    }
    i = 63;
    while (i >= 0) {
        if ((two_ >> i) & 1){
            cnt++;
        }
        i--;
    }
    return cnt;
}
bool BitString::operator <(BitString& a) {
    return this->count() < a.count(); 
}
bool BitString::operator >(BitString& a) {
    return this->count() > a.count(); 
}
bool BitString::operator ==(BitString& a) {
    return this->count() == a.count(); 
}
bool BitString::include(BitString& other) {
    BitString s = other&(*this);
    return s==other;
}
BitString::~BitString(){
}