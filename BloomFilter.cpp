#include "BloomFilter.h"

#define TOTAL_HASH_FUNCTIONS 16

BloomFilter::BloomFilter(int size) : size(size) {
    bitset = new unsigned char[size];
    clear();
}

BloomFilter::~BloomFilter() {
    delete [] bitset;
}

//creates the bloom filter of given size and puts 0 on each bit
BloomFilter::BloomFilter(const BloomFilter& other) : size(other.size) {
    bitset = new unsigned char[other.size];

    for (int i = 0; i < other.size; i++) {
        bitset[i] = other.bitset[i];
    }
}
//size is given in bits
void BloomFilter::insert(string object) {
    unsigned char * str = (unsigned char *) object.c_str();

    for (int i = 0; i < TOTAL_HASH_FUNCTIONS; i++) {
        int bitno = hash_i(str, i) % (size*8); //calculate the position we need(*8 gives us the bit we want)

        (*this)[bitno] = (*this)[bitno] | (1 << (bitno % 8)); //this gives us the byte we want
    }
}

unsigned char & BloomFilter::operator[](int bitno) {
    int idx = bitno / 8;

    return bitset[idx];
}
//checks if the object is contained.note that we can get a false positive
//this case is checked at the correct places
bool BloomFilter::contains(string object) {
    unsigned char * str = (unsigned char *) object.c_str();

    for (int i = 0; i < TOTAL_HASH_FUNCTIONS; i++) {
        int bitno = hash_i(str, i) % (size*8);
        
        if (((*this)[bitno] & (1 << (bitno % 8))) == 0) {
            return false;
        }        
    }
    return true;
}
//clears the bloom filter by assigning the value 0 to all the bits
void BloomFilter::clear() {
    for (int i = 0; i < size; i++) {
        bitset[i] = 0;
    }
}

unsigned long BloomFilter::djb2(unsigned char *str) {
    int c;
    unsigned long hash = 5381;

    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

unsigned long BloomFilter::sdbm(unsigned char *str) {
    int c;
    unsigned long hash = 0;

    while ((c = *str++) != '\0') {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned long BloomFilter::hash_i(unsigned char *str, unsigned int i) {
    return djb2(str) + i * sdbm(str) + i * i;
}