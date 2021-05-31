
#ifndef OPERATORS_H
#define OPERATORS_H

#include <string>

#include "BinarySearchTree.h"
#include "Citizen.h"
#include "Disease.h"
#include "Country.h"

using namespace std;

Country & operator>>(Country & country, BinarySearchTree * b);

Citizen & operator>>(Citizen & citizen, BinarySearchTree * b);

Disease & operator>>(Disease & disease, BinarySearchTree * b) ;


#endif /* OPERATORS_H */

