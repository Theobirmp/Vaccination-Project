
#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include  <string>

using namespace std;

class BloomFilter {
public:
    BloomFilter(int size);
    virtual ~BloomFilter();
    
    BloomFilter(const BloomFilter& other) ;


    void insert(string object);
    bool contains(string object);
    void clear();
    
    unsigned char & operator[](int bitno);
private:
    int size;
    unsigned char * bitset;

    unsigned long djb2(unsigned char *str);

    unsigned long sdbm(unsigned char *str);

    unsigned long hash_i(unsigned char *str, unsigned int i);
};


#endif /* BLOOMFILTER_H */

