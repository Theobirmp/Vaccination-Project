
#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <string>

#include "Data.h"

using namespace std;

class Country : public Data {
public:
    string name;
    int population; //the popoulation of a given country-not really needed-check README

    Country(string name);
    virtual ~Country();
    //more on overloading on README
    virtual bool operator<(const Data& right) const;
    virtual bool operator>(const Data& right) const;

    virtual void print(ostream & out) const;
    
    virtual int compare(const string key) const;

};


#endif /* COUNTRY_H */

