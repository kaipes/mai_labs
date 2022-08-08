#include <stdio.h>
#include "library.h"
#include <stdbool.h>
void init (struct Bitset* bs){
    bs->set = 0;
}
void makeIntersect (struct Bitset* bs, const struct Bitset r){
    bs->set = bs->set & r.set;
}
void addElement(struct Bitset* bs, unsigned i){
        bs->set = bs->set | (1ull << (i - 1040));
}
unsigned utf8ToUnicode (unsigned char firstByte, unsigned char secondByte){
    unsigned firstDigit = firstByte & 31;
    unsigned secondDigit = secondByte & 63;
    return (firstDigit << 6) | secondDigit;
}
void text(struct Bitset* bs, unsigned element){
		bs->set = bs->set | (1u << 6); 
}
void printSet (struct Bitset* const bs)
{
const unsigned maxBitsetType = sizeof(BitsetType) * 8;
for (int i = maxBitsetType - 1; i >= 0; --i)
    {
    bool isCurrentValZero = (bs->set & (1u << i)) == 0;
    if (isCurrentValZero) {
        printf ("0");
    }
    else {
       printf ("1");
        }
    }
    printf("\n");
}
