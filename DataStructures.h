#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include "BinarySearchTree.h"


class DataStructures {
public:
    BinarySearchTree * bst_citizens;
    BinarySearchTree * bst_countries;
    BinarySearchTree * bst_diseases;    

    DataStructures();
    DataStructures(const DataStructures& orig);
    virtual ~DataStructures();
    
    void display();
private:

};

#endif /* DATASTRUCTURES_H */

