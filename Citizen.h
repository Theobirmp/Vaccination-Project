
#ifndef CITIZEN_H
#define CITIZEN_H

#include <iostream>

#include "Data.h"

using namespace std;

class Citizen : public Data {
public:
    int id;
    string firstname, lastname, country, age;

    Citizen(int id, string firstname, string lastname, string country, string age);
    virtual ~Citizen();

    virtual bool operator<(const Data& right) const;
    virtual bool operator>(const Data& right) const;

    virtual void print(ostream & out) const;
    
    virtual int compare(const string key) const;
private:

};




#endif /* CITIZEN_H */

