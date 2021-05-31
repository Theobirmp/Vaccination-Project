#ifndef DISEASE_H
#define DISEASE_H

#include "Data.h"
#include "BloomFilter.h"
#include "SkipList.h"

#include <string>

using namespace std;
//each disease needs to have a name a bloom filter and two skip lists(none for vacinated and one for not vacinated)
class Disease : public Data {
public:
    string name;
    BloomFilter filter;
    SkipList vaccinated;
    SkipList not_vaccinated;

    Disease(string name, int bytes, int levels);
    virtual ~Disease();
    //more on overloading on README
    virtual bool operator<(const Data& right) const;
    virtual bool operator>(const Data& right) const;

    virtual void print(ostream & out) const;
    virtual void print(ostream & out, bool vaccinated) const;
    
    virtual int compare(const string key) const;
private:

};

#endif /* DISEASE_H */

