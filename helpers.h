
#ifndef HELPERS_H
#define HELPERS_H


#include <string>

#include "Date.h"

using namespace std;

//check cpp file for implementation and comments
int string_into_int(const string& s);

int args_string_to_int(string& x);

string remove_random_chars(string& s );

bool is_date(string s);

bool is_number(const string& s);

Date* get_current_date();

string date_to_string(Date date);

#endif /* HELPERS_H */

