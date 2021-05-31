#ifndef SEARCHFILTER_H
#define SEARCHFILTER_H

#include <string>
#include <iostream>

using namespace std;
using namespace std;
//used to make searching easier
class SearchFilter {
public:
    string country;
    string date1;
    string date2;
    class Disease * disease;

    
    SearchFilter(string country, string date1, string date2, class Disease* disease) : country(country), date1(date1), date2(date2), disease(disease) {
    }


    SearchFilter(const SearchFilter& other) : country(other.country), date1(other.date1), date2(other.date2), disease(other.disease) {
    }


};

#endif /* SEARCHFILTER_H */

