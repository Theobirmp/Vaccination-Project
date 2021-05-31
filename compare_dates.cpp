#include <iostream>
#include <string>
#include <sstream>

#include "Date.h"
#include "helpers.h"

using namespace std;



//used to swap dates if they are not in the correct order

void swap_dates(Date& d1, Date& d2) {
    Date temp;

    temp.day = d1.day;
    temp.month = d1.month;
    temp.year = d1.year;
    temp.days_date = d1.days_date;

    d1.day = d2.day;
    d1.month = d2.month;
    d1.year = d2.year;
    d1.days_date = d2.days_date;

    d2.day = temp.day;
    d2.month = temp.month;
    d2.year = temp.year;
    d2.days_date = temp.days_date;
}

//checks if the first date is between thesecond and the third

bool date_compare(string d1, string d2, string d3) {
    string delimiter = "-";
    Date date1, date2, date3;

    //find the day
    date1.day = d1.substr(0, d1.find(delimiter));
    date2.day = d2.substr(0, d2.find(delimiter));
    date3.day = d3.substr(0, d3.find(delimiter));

    //remove the day and the '-' from the string
    d1 = d1.erase(0, date1.day.size() + 1); //+1 is used to target the delimiter character
    d2 = d2.erase(0, date2.day.size() + 1);
    d3 = d3.erase(0, date3.day.size() + 1);

    //access the month
    date1.month = d1.substr(0, d1.find(delimiter));
    date2.month = d2.substr(0, d2.find(delimiter));
    date3.month = d3.substr(0, d3.find(delimiter));

    //remove the month and the '-' from the string
    d1 = d1.erase(0, date1.month.size() + 1);
    d2 = d2.erase(0, date2.month.size() + 1);
    d3 = d3.erase(0, date3.month.size() + 1);

    //access the year
    date1.year = d1;
    date2.year = d2;
    date3.year = d3;

    //instead of converting strings into ints we store into days_date how many days have passed from 0-0-0
    //these will help us find if the wanted date is between the two others
    int temp_days;
    //calculation of days_date for date1
    temp_days = string_into_int(date1.day);
    date1.days_date = temp_days * 1;
    
    temp_days = string_into_int(date1.month);
    date1.days_date = date1.days_date + temp_days * 30;
    
    temp_days = string_into_int(date1.year);
    date1.days_date = date1.days_date + temp_days * 365;
    
    //calculation of days_date for date2
    temp_days = string_into_int(date2.day);
    date2.days_date = temp_days * 1;
    
    temp_days = string_into_int(date2.month);
    date2.days_date = date2.days_date + temp_days * 30;
    
    temp_days = string_into_int(date2.year);
    date2.days_date = date2.days_date + temp_days * 365;
    
    //calculation of days_date for date3
    temp_days = string_into_int(date3.day);
    date3.days_date = temp_days * 1;
    
    temp_days = string_into_int(date3.month);
    date3.days_date = date3.days_date + temp_days * 30;
    
    temp_days = string_into_int(date3.year);
    date3.days_date = date3.days_date + temp_days * 365;

    if (date2.days_date > date3.days_date) {
        swap_dates(date2, date3);
    }

    //we need to check if the first date lives between the other two ones
    //we could use the if statement from above but for three days.However,there is a better method. We are going to multiply the number of the year with 365 and
    //the number of the month by 30(each month has 30 days). This way we count how many days have passed from 0 and we can compare dates much easier
    //the first date is between the second and the third
    if (date1.days_date >= date2.days_date && date1.days_date <= date3.days_date) {
        return true;
    } else {
        return false;
    }
}

bool date_compare(Date date, string d2, string d3) {
    string d1 = date_to_string(date);
    return date_compare(d1, d2, d3);
}
