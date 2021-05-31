
#include <stddef.h>


#include "operators.h"
#include "Country.h"
#include "Citizen.h"
#include "Disease.h"
//there is a lot more overloading happening on operators
////more on overloading on README
//these  overloaded operators(same one three times) is used to insert into the binary tree
Country & operator>>(Country & country, BinarySearchTree * b) {
    if (b->search(&country) == NULL) {
        cout << country.name << endl;
        Country * newcountry = new Country(country);
        b->insert(newcountry);
        return *newcountry;
    } else {
        Country * existing = (Country *) b->search(&country);
        existing->population++;
        return *existing;
    }
}

Citizen & operator>>(Citizen & citizen, BinarySearchTree * b) {
    if (b->search(&citizen) == NULL) {
        Citizen * newcitizen = new Citizen(citizen);
        b->insert(newcitizen);
        return *newcitizen;
    } else {
        Citizen * existing = (Citizen *) b->search(&citizen);
        return *existing;
    }
}

Disease & operator>>(Disease & disease, BinarySearchTree * b) {
    if (b->search(&disease) == NULL) {
        Disease * newdisease = new Disease(disease);
        b->insert(newdisease);
        return *newdisease;
    } else {
        Disease * existing = (Disease *) b->search(&disease);
        return *existing;
    }
}
