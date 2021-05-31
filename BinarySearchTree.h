
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <string>

#include "Data.h"
#include "VaccineData.h"
#include "SearchFilterByAge.h"

using namespace std;

class BinarySearchTree {
public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    //type Data is used so that we use one implementation of the tree for all our data types
    //citizen disease and country are all housed in the same tree implementation
    //ofc different tree is allocated each time
    void insert(Data * x);

    void remove(Data * key);

    void display();

    Data * search(Data * key);
    
    Data * search(string key);

    void inorder_process_data(VaccineData * vacdata); // vaccineStatus
    
    void inorder_process_data(SearchFilter & filter); // populationStatus
    
    void inorder_process_data(SearchFilterByAge & filter); // popStatusByAge
private:

    class Node {
    public:
        Data * data;
        Node* left;
        Node* right;
    } * root;

    Node* destroy(Node* t);

    Node* insert(Data * x, Node* t);

    Node* findMin(Node* t);

    Node* findMax(Node* t);

    Node* remove(Data * key, Node* t);

    void inorder(Node* t);

    Node* find(Node* t, Data * key);
    
    Node* find(Node* t, string key);

    
    void inorder_process_data(Node* t, VaccineData * vacdata);
    
    void inorder_process_data(Node* t, SearchFilter & filter);
    
    void inorder_process_data(Node* t, SearchFilterByAge & filter);
};

#endif /* BINARYSEARCHTREE_H */

