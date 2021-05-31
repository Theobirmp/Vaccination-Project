#include "VaccineData.h"
#include "helpers.h"

VaccineData::VaccineData(Date date, Citizen* citizen) : Data(), date(date), citizen(citizen) {
}

VaccineData::VaccineData() : Data(), citizen(NULL) {
}

VaccineData::~VaccineData() {

}

VaccineData::VaccineData(Citizen * citizen) : Data(), date(), citizen(citizen)  {
    
}

bool VaccineData::operator<(const Data& right) const {
    const VaccineData * c = dynamic_cast<const VaccineData*> (&right);

    if (c == NULL) {
        //this should never get printed
        cout << "sth went terribly wrong - vac data <" << endl;
        exit(1);
    }

    if (c->citizen == NULL) {
        return true;
    }

    if (this->citizen == NULL) {
        return false;
    }

    return this->citizen->id < c->citizen->id;
}

bool VaccineData::operator>(const Data& right) const {
    const VaccineData * c = dynamic_cast<const VaccineData*> (&right);

    if (c == NULL) {
        //this should never be executed
        cout << "sth went terribly wrong - vac data >" << endl;
        exit(1);
    }

    if (c->citizen == NULL) {
        return false;
    }

    if (this->citizen == NULL) {
        return true;
    }

    return this->citizen->id > c->citizen->id;
}

bool VaccineData::operator==(const Data& right) const {
    const VaccineData * c = dynamic_cast<const VaccineData*> (&right);

    if (c == NULL) {
        //this should never be executed
        cout << "sth went terribly wrong  - vac data ==" << endl;
        exit(1);
    }

    if (c->citizen == NULL) {
        return false;
    }

    if (this->citizen == NULL) {
        return false;
    }
    //reminder: this operator is overloaded
    return this->citizen->id == c->citizen->id;
}

bool VaccineData::operator==(const SearchFilter & filter) const {
    //each case is written on the right
    if (filter.country != "" && filter.date1 != "" && filter.date2 != "") { // c d d 
        return this->citizen->country == filter.country && date_compare(this->date, filter.date1, filter.date2);
    }
    
    if (filter.country != "" && filter.date1 == "" && filter.date2 == "") { // c
        return this->citizen->country == filter.country;
    }
    
    if (filter.country == "" && filter.date1 != "" && filter.date2 != "") { // d d
        return date_compare(this->date, filter.date1, filter.date2);
    }
    
    if (filter.country == "" && filter.date1 == "" && filter.date2 == "") { // -
        return true;
    }
    
    return false;
}

bool VaccineData::operator==(const SearchFilterByAge & filter) const {
    int age= string_into_int(this->citizen->age);
    //each case is written on the right
    if (filter.country != "" && filter.date1 != "" && filter.date2 != "") { // c d d 
        return this->citizen->country == filter.country && date_compare(this->date, filter.date1, filter.date2) && age >= filter.min_age && age <= filter.max_age;
    }
    
    if (filter.country != "" && filter.date1 == "" && filter.date2 == "" && age >= filter.min_age && age <= filter.max_age) { // c
        return this->citizen->country == filter.country;
    }
    
    if (filter.country == "" && filter.date1 != "" && filter.date2 != "" && age >= filter.min_age && age <= filter.max_age) { // d d
        return date_compare(this->date, filter.date1, filter.date2);
    }
    
    if (filter.country == "" && filter.date1 == "" && filter.date2 == "" && age >= filter.min_age && age <= filter.max_age) { // -
        return true;
    }
    
    return false;
}

void VaccineData::print(ostream & out) const {
    out << *this->citizen;
    
    if (date.day != "") {
        date.print();
    }
}
//this is not used
//there exists another compare
//used for debugging
int VaccineData::compare(const string key) const {
    exit(9);
}