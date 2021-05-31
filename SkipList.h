#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <string>
#include <iostream>

#include "Data.h"
#include "VaccineData.h"
#include "SearchFilterByAge.h"

using namespace std;

class SkipList {
public:
    SkipList(int maxlevel);
    virtual ~SkipList();
    SkipList(const SkipList& other);
    
    string insert(VaccineData * add_data);
    void remove(VaccineData * del_data);
    void print(ostream & out) const;
    Data * search(Data * search_data);
    
    int count(SearchFilter & searchFilter);
    
    float * count(SearchFilterByAge & searchFilter);

private:

    struct Node {
        VaccineData* data;
        Node** node_ptr;
    };
    
    int maxlevel;
    
    Node* head;
    Node* termination;
    Node* curr;
    Node* temp;
};

#endif /* SKIPLIST_H */

