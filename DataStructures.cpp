#include "DataStructures.h"

DataStructures::DataStructures() {
    //creates the three trees
    //note that there is one implementation of a tree
    //but 3 trees are being used that store different types
    bst_citizens = new BinarySearchTree();
    bst_countries = new BinarySearchTree();
    bst_diseases = new BinarySearchTree();
}

DataStructures::DataStructures(const DataStructures& orig) {
    
}

DataStructures::~DataStructures() {
    delete bst_citizens;
    delete bst_countries;
    delete bst_diseases;
}


void DataStructures::display() {
    //uses the display function of the tree data structure-class
    bst_citizens->display();
    bst_countries->display();
    bst_diseases->display();
}