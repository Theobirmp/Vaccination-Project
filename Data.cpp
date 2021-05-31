#include "Data.h"

Data::Data() {

}

Data::Data(const Data& orig) {

}

Data::~Data() {

}

bool Data::operator==(const Data& right) const {
    //we use the two operators we created to create the ==
    return !((*this) < right) && !((*this) > right);
}

void Data::print(ostream & out) const {
    //never used
}
//more on overloading on README
bool Data::operator==(const SearchFilter & filter) const {
    return false;
}
ostream & operator<<(ostream & left, const Data &right) {
    right.print(left);
    return left;
}
//compare returns a value depending on the result
//0 -1 +1 
bool operator<(const string& left, const Data &right) { // string < data
    return right.compare(left) > 0;
}

bool operator<(const Data &left, const string& right) {
    return left.compare(right) < 0;
}

bool operator>(const string& left, const Data &right) {
    return right.compare(left) < 0;
}

bool operator>(const Data &left, const string& right) {
    return left.compare(right) > 0;
}

bool operator==(const string& left, const Data &right) {
    return right.compare(left) == 0;
}

bool operator==(const Data &left, const string& right) {
    return left.compare(right) == 0;
}