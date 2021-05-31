#include "Citizen.h"
#include "helpers.h"

#include <iostream>

using namespace std;

Citizen::Citizen(int id, string firstname, string lastname, string country, string age) : Data(), id(id), firstname(firstname), lastname(lastname), country(country), age(age) {
}

Citizen::~Citizen() {

}
bool Citizen::operator<(const Data& right) const {
    //dynamic cast is needed to change the type from Data 
    const Citizen * c = dynamic_cast<const Citizen*> (&right);
    //this should never be printed-if it is sth we went terribly wrong
    if (c == NULL) {
        cout << "oime kai tris ali Citizen < " << endl;
        exit(1);
    }
    //note that operators are overloaded so comparisons like these work the way they are intended to(default comparison in this case causes errors)
    return this->id < c->id;
}

bool Citizen::operator>(const Data& right) const {
    //dynamic cast is needed to change the type from Data 
    const Citizen * c = dynamic_cast<const Citizen*> (&right);

    if (c == NULL) {
        cout << "oime kai tris ali Citizen > " << endl;
        exit(1);
    }

    return this->id > c->id;
}
//typical print function
void Citizen::print(ostream & out) const {
    out << this->id << " ";
    out << this->firstname << " ";
    out << this->lastname << " ";
    out << this->country << " ";
    out << this->age << "\n";
}
//compares id with a string
//NOTE::id is a string
//the operators are overloaded because the default comparison wields wrong results
int Citizen::compare(const string key) const {
    int value = string_into_int(key);
    
    if (this->id == value) {
        return 0;
    } else if (this->id < value) {
        return -1;
    } else {
        return +1;
    }    
}