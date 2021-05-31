
#ifndef VACCINEDATA_H
#define VACCINEDATA_H

#include <iostream>

#include "Date.h"
#include "Data.h"
#include "Citizen.h"
#include "SearchFilterByAge.h"

using namespace std;

class VaccineData : public Data {
public:
    Date date;
    Citizen * citizen;

    VaccineData();
    VaccineData(Citizen * citizen);
    VaccineData(Date date, Citizen* citizen);
    virtual ~VaccineData();
    
    VaccineData(const VaccineData& other) : Data(other), date(other.date), citizen(other.citizen) {
    }

    //more on operatos on README
    virtual bool operator<(const Data& right) const;
    virtual bool operator>(const Data& right) const;
    virtual bool operator==(const Data& right) const;
    virtual bool operator==(const SearchFilter & filter) const;
    virtual bool operator==(const SearchFilterByAge & filter) const;

    virtual void print(ostream & out) const;
    
    virtual int compare(const string key) const;
private:

};

#endif /* VACCINEDATA_H */

