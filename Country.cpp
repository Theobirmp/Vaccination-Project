#include "Country.h"

#include <iostream>

using namespace std;

//more on overloading on README

Country::Country(string name) : name(name), population(0) {

}

Country::~Country() {

}


bool Country::operator<(const Data& right) const {    
    //dynamic cast is needed to change the type from Data 
    const Country * c = dynamic_cast<const Country*>(&right);
    
    if (c== NULL) {
        cout << "oime kai tris ali Country <" << endl;
        exit(1);
    }
        
    return this->name < c->name;
}

bool Country::operator>(const Data& right) const { 
    //dynamic cast is needed to change the type from Data    
    const Country * c = dynamic_cast<const Country*>(&right);
    
    if (c== NULL) {
        cout << "oime kai tris ali Country >" << endl;
        exit(1);
    }
        
    return this->name > c->name;
}


void Country::print(ostream & out) const {
    out << this->name << endl;
}

int Country::compare(const string key) const {
    if (this->name == key) {
        return 0;
    } else if (this->name < key) {
        return -1;
    } else {
        return +1;
    }    
}