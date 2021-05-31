#include "Disease.h"

Disease::Disease(string name, int bytes, int levels) : name(name), filter(bytes), vaccinated(levels), not_vaccinated(levels) {
//disease consists of the two skip lists-these are created whenever a new disease is found hence created(instansiated)
}

Disease::~Disease() {

}
//more on overloading on README
bool Disease::operator<(const Data& right) const {
    //dynamic cast is needed to change the type from Data 
    const Disease * c = dynamic_cast<const Disease*> (&right);

    if (c == NULL) {
        //this means that sth went really wrong-should never see this one
        cout << "oime kai tris ali - disease <" << endl;
        exit(1);
    }

    return this->name < c->name;
}

bool Disease::operator>(const Data& right) const {
    //dynamic cast is needed to change the type from Data 
    const Disease * c = dynamic_cast<const Disease*> (&right);

    if (c == NULL) {
        //this means that sth went really wrong-should never see this one
        cout << "oime kai tris ali - disease >" << endl;
        exit(1);
    }

    return this->name > c->name;
}

void Disease::print(ostream & out) const {
    out << this->name << "\n";
    
}

void Disease::print(ostream & out, bool vaccinated) const {
    out << this->name << "\n";
    
    if (vaccinated) {
        this->vaccinated.print(out);
    }
    
    if (!vaccinated) {
        this->not_vaccinated.print(out);
    }
}
int  Disease::compare(const string key) const {
    //used to compare the given disease->name with a key
    if (this->name == key) {
        return 0;
    } else if (this->name < key) {
        return -1;
    } else {
        return +1;
    }   
}
