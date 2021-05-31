#ifndef SEARCHFILTER_BY_AGE_H
#define SEARCHFILTER_BY_AGE_H

#include <string>
#include <iostream>

using namespace std;
//used to make searching easier
class SearchFilterByAge {
public:
    string country;
    string date1;
    string date2;
    class Disease * disease;
    int min_age;
    int max_age;

    
    SearchFilterByAge(string country, string date1, string date2, class Disease* disease) : country(country), date1(date1), date2(date2), disease(disease), min_age(0), max_age(0) {
        
    }


    SearchFilterByAge(const SearchFilterByAge& other) : country(other.country), date1(other.date1), date2(other.date2), disease(other.disease), min_age(other.min_age), max_age(other.max_age) {
    }


};

#endif /* SEARCHFILTER_H */

