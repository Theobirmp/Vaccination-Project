
#include <iostream>
#include <string>

using namespace std;

#include "Date.h"
#include "helpers.h"
//days_date is used to compare dates in a more efficient fashion-check compare_dates in helpers.cpp for more info
Date::Date() {
    day ="";
    month = "";
    year ="";
    days_date = 0;
}
//used to create the object date
//we substr each element of the string to insert to the corresponding values
//mind the delimiters-we need to erase them
Date::Date(string s) {
    string delimiter = "-";
    string s1, s2, s3;
    s1 = s.substr(0, s.find(delimiter));
    s = s.erase(0, s.find(delimiter) + 1);
    s2 = s.substr(0, s.find(delimiter));
    s = s.erase(0, s.find(delimiter) + 1);
    s3 = s.substr(0, s.find(delimiter));
    //check helpers.cpp for implementation of is_number
    if (is_number(s1) && is_number(s2) && is_number(s3)) {
        day = s1;
        month = s2;
        year = s3;
    } else {
        cout << "invalid date format: " << s << endl;
        exit(1);
    }
}

void Date::print() const {
    cout << day << "/" << month << "/" << year << endl;
}