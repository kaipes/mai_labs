typedef unsigned long long BitsetType;
    struct Bitset {
        BitsetType set;
    };
void init (struct Bitset* bs);
void makeIntersect (struct Bitset* bs, const struct Bitset r);
void addElement (struct Bitset* bs, unsigned i);
unsigned utf8ToUnicode (unsigned char firstByte, unsigned char secondByte);
void printSet (struct Bitset* bs);
void makeComplement (struct Bitset* bs);