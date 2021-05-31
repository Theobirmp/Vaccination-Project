#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

using namespace std;


//type Date used to store the dates
//sometimes it was easier to deal with dates as strings
//this type is mainly used to compare dates
//int dates is used to calcuate how many days have past till 0-0-0
//this is used to make the comparison faster and less tedious
class Date {
public:
    string day;
    string month;
    string year;
    int days_date; //days past till 0-0-0 ->used to compare dates
    
    
    Date();
    
    Date(string s);
    
    void print() const;
};

bool date_compare(string d1, string d2, string d3);

bool date_compare(Date date, string d2, string d3);

#endif /* DATE_H */

