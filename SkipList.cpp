#include "SkipList.h"


#include <iostream>


using namespace std;

SkipList::SkipList(int maxlevel) : maxlevel(maxlevel) {
    curr = NULL;
    temp = NULL;

    head = new SkipList::Node();
    head->data = new VaccineData();
    head->node_ptr = new SkipList::Node*[maxlevel](); //creates nodes for each level
    //note that the first and last nodes are special
    //data is not stored in them
    //they just store junk so that we know when the skip list starts and ends
    termination = new SkipList::Node();
    termination->data = new VaccineData();
    termination->node_ptr = NULL;
    //when created the skip list is empty
    //hence all pointers point to the termination node
    for (int i = 0; i < maxlevel; i++) {
        head->node_ptr[i] = termination;
    }
}
//this is another constructor
//it is used to insert vac data in the skiplist
SkipList::SkipList(const SkipList& other) : maxlevel(other.maxlevel) {
    curr = NULL;
    temp = NULL;

    head = new SkipList::Node();
    head->data = new VaccineData();
    head->node_ptr = new SkipList::Node*[maxlevel]();

    termination = new SkipList::Node();
    termination->data = new VaccineData();
    termination->node_ptr = NULL;

    for (int i = 0; i < maxlevel; i++) {
        head->node_ptr[i] = termination;
    }

    Node* other_curr = other.head->node_ptr[0];

    while (other_curr != other.termination) {

        this->insert(new VaccineData(*other_curr->data));
        other_curr = other_curr->node_ptr[0];
    }

}
//destructor
//we need to be careful when we destroy the skip list-remember that there is junk in the first and last node
SkipList::~SkipList() {
    temp = head;
    curr = head;
    //while there is next node-while the next node has data(remember the last one has junk)
    while (curr != NULL) {
        if (curr->node_ptr != NULL && curr->node_ptr[0] != NULL) {
            curr = curr->node_ptr[0];
        } else {
            curr = NULL;
        }

        if (temp->data != NULL) {
            delete temp->data;
        }
        if (temp->node_ptr != NULL) {
            delete [] temp->node_ptr;
        }

        delete temp;

        temp = curr;
    }
}

string SkipList::insert(VaccineData * add_data) {
    SkipList::Node * update[this->maxlevel];

    curr = head;
    //we need to find where to insert the data
    //we run across the top "list" of the skip list
    //we traverse the next level if the next value is bigger than the one we want 
    for (int i = maxlevel - 1; i >= 0; i--) {
        while (*curr->node_ptr[i]->data < *add_data) {
            curr = curr->node_ptr[i];
        }

        update[i] = curr;
    }

    curr = curr->node_ptr[0];
    //if we find it
    if (curr->data != NULL && *(curr->data) == *add_data) {
        return "ALREADY EXISTS";
    } else {
        int level = rand() % this->maxlevel;

        SkipList::Node * n = new SkipList::Node();
        n->data = add_data;
        n->node_ptr = new SkipList::Node*[maxlevel]();
        //insert
        for (int i = 0; i <= level; i++) {
            n->node_ptr[i] = update[i]->node_ptr[i];
            update[i]->node_ptr[i] = n;
        }
    }

    return "Command successful";

}
//we need to remove the node and fix the pointers
//this implementation follows the typical implementation
//of a singly linked list
//just with more levels

void SkipList::remove(VaccineData * del_data) {
    SkipList::Node * update[this->maxlevel];

    curr = head;

    for (int i = maxlevel - 1; i >= 0; i--) {
        while (*curr->node_ptr[i]->data < *del_data) {
            curr = curr->node_ptr[i];
        }

        update[i] = curr;
    }

    curr = curr->node_ptr[0];

    if (curr->data != NULL && *(curr->data) == *del_data) {
        for (int i = 0; i < maxlevel; i++) {
            if (update[i]->node_ptr[i] != curr) {
                break;
            }
            update[i]->node_ptr[i] = curr->node_ptr[i];
        }
        delete[] curr->node_ptr;
        delete curr->data;
        delete curr;
    }
}

void SkipList::print(ostream & out) const {
    Node* curr = head;
    //to print we go to the base level
    curr = curr->node_ptr[0];

    while (curr != NULL) {
        if (curr->node_ptr == NULL) {
            break;
        }
        curr->data->print(out);
        curr = curr->node_ptr[0];
    }
}

Data * SkipList::search(Data * search_data) {
    curr = head;
    //we start from the top level and traverse to the next ones the same way
    //we did in the code above
    for (int i = maxlevel - 1; i >= 0; i--) {
        while (*curr->node_ptr[i]->data < *search_data) {
            curr = curr->node_ptr[i];
        }
    }

    curr = curr->node_ptr[0];

    if (curr->data != NULL && *(curr->data) == *search_data) {
        return curr->data;
    } else {
        return NULL;
    }
}
//returns a counter- needed for when we count e.g. how many people have been vacinated in  country
//checks the bottom level since this is the one that has all the data(skips none)
int SkipList::count(SearchFilter & searchFilter) {
    curr = head->node_ptr[0];

    int counter = 0;

    while (curr != NULL && curr != termination) {
        if (*(curr->data) == searchFilter) {
            counter++;
        }

        curr = curr->node_ptr[0];
    }

    return counter;
}
//does the same job as above-this is used only for the popstatusbyage function
float * SkipList::count(SearchFilterByAge & searchFilter) {
    curr = head->node_ptr[0];

    float * counters = new float [4];

    for (int i = 0; i < 4; i++) {
        counters[i] = 0.0f;
    }

    while (curr != NULL && curr != termination) {
        searchFilter.min_age = 0;
        searchFilter.max_age = 19;

        if (*(curr->data) == searchFilter) {
            counters[0]++;
        }

        searchFilter.min_age = 20;
        searchFilter.max_age = 39;

        if (*(curr->data) == searchFilter) {
            counters[1]++;
        }

        searchFilter.min_age = 40;
        searchFilter.max_age = 59;

        if (*(curr->data) == searchFilter) {
            counters[2]++;
        }

        searchFilter.min_age = 60;
        searchFilter.max_age = 120;

        if (*(curr->data) == searchFilter) {
            counters[3]++;
        }

        curr = curr->node_ptr[0];
    }

    return counters;
}