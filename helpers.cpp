#include "helpers.h"
#include <ctime>
#include <sstream>


using namespace std;

//basic functions used throughout the excercise

//checks if a string is a number(used to check if a "date" is a actually a date)
//used mainly in error checking-debugging
bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
//converts a string to int
int string_into_int(const string& s) {
    stringstream sso(s);
    int x = 0;
    sso>>x;
    return x;
}

//-b and -c are converted to numbers (- is erased)
int args_string_to_int(string& x) {
    int num;
    x = x.erase(0, x.find("-") + 1);
    num = string_into_int(x);
    return num;
}
//parses a string and checks if it is a date (used is_number to check if the substrings are actually numbers)
bool is_date(string s) {
    string delimiter = "-";
    string s1, s2, s3;
    s1 = s.substr(0, s.find(delimiter));
    s = s.erase(0, s.find(delimiter) + 1);
    s2 = s.substr(0, s.find(delimiter));
    s = s.erase(0, s.find(delimiter) + 1);
    s3 = s.substr(0, s.find(delimiter));
    if (is_number(s1) && is_number(s2) && is_number(s3)) return true;
    return false;
}
//returns a string from an object date-propably never used?
string date_to_string(Date date) {
    return date.day + "-" + date.month + "-" + date.year;
}

//used at command parsing- user can insert commands with .command ./command or even command (plus other combinations not so common)
string remove_random_chars(string& s) {//used so we can call functions with ./ or / or raw
    for (int i = 0; i < s.size(); i++) {

        // Finding the character whose  
        // ASCII value fall under this 
        // range 
        if (s[i] < 'A' || s[i] > 'Z' &&
                s[i] < 'a' || s[i] > 'z') {
            // erase function to erase  
            // the character 
            s.erase(i, 1);
            i--;
        }
    }
    return s;
}

//returns the current date of the system
//used once
Date* get_current_date() {
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    string day = to_string(timePtr->tm_mday);
    string month = to_string(timePtr->tm_mon);
    string year = to_string(timePtr->tm_year + 1900);

    string date = day + "-" + month + "-" + year;

    Date* d = new Date(date);
    return d;
}