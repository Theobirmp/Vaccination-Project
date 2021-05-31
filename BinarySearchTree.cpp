#include "BinarySearchTree.h"
#include "Disease.h"
#include "Country.h"

#include <iostream>

using namespace std;

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    //destroy is a recursive function.it destroys the subtree of the node we pass it
    //if we pass the root it obviously destroys the whole tree
    root = destroy(root);
}

void BinarySearchTree::insert(Data * x) {
    root = insert(x, root);
}

void BinarySearchTree::remove(Data * x) {
    root = remove(x, root);
}
//displays the sub tree of the argument given-if it is the root then it dislays the whole tree
void BinarySearchTree::display() {
    inorder(root);
    cout << endl;
}
//uses the find subfunction to search in the tree-searches with data
Data * BinarySearchTree::search(Data * key) {
    BinarySearchTree::Node* n = find(root, key);
    if (n == NULL) {
        return NULL;
    } else {
        return n->data;
    }
}
//uses the find subfunction to search in the tree-searches with string
Data * BinarySearchTree::search(string key) {
    BinarySearchTree::Node* n = find(root, key);
    if (n == NULL) {
        return NULL;
    } else {
        return n->data;
    }
}

BinarySearchTree::Node* BinarySearchTree::destroy(BinarySearchTree::Node* t) {
    if (t == NULL) {
        return NULL;
    }

    destroy(t->left);
    destroy(t->right);

    delete t->data;
    delete t;
    return NULL;
}
//inserts to the corresponding tree
//remember that one tree implementation is being used for all the trees
//this means we have to overload many operators so that we can insert the appropriate type to its corresponding tree
BinarySearchTree::Node* BinarySearchTree::insert(Data * x, BinarySearchTree::Node* t) {
    if (t == NULL) {
        t = new Node();
        t->data = x;
        t->left = t->right = NULL;
    } else if (*x < *t->data)
        t->left = insert(x, t->left);
    else if (*x > *t->data)
        t->right = insert(x, t->right);
    return t;
}
//find min function - the most usual implementation-nothing out of the ordinary
BinarySearchTree::Node* BinarySearchTree::findMin(BinarySearchTree::Node* t) {
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return findMin(t->left);
}
//find max function - the most usual implementation-nothing out of the ordinary
BinarySearchTree::Node* BinarySearchTree::findMax(BinarySearchTree::Node* t) {
    if (t == NULL)
        return NULL;
    else if (t->right == NULL)
        return t;
    else
        return findMax(t->right);
}

BinarySearchTree::Node* BinarySearchTree::remove(Data * x, BinarySearchTree::Node* t) {
    //recursive until it finds the data we want-then we fix the pointers
    //if its a leaf we are ok
    //if not we need to fix the pointers-remember that if left pointer is null then the right one is also null
    //if right one is null then make t point to the left child
    Node* temp;
    if (t == NULL)
        return NULL;
    else if (*x < *t->data)
        t->left = remove(x, t->left);
    else if (*x > *t->data)
        t->right = remove(x, t->right);
    else if (t->left && t->right) {
        temp = findMin(t->right);
        t->data = temp->data;
        t->right = remove(t->data, t->right);
    } else {
        temp = t;
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        delete temp;
    }

    return t;
}

void BinarySearchTree::inorder(BinarySearchTree::Node* t) {
    //prints the content of the whole tree
    if (t == NULL) {
        return;
    }
    inorder(t->left);
    cout << *(t->data) << " ";
    inorder(t->right);
}

BinarySearchTree::Node* BinarySearchTree::find(BinarySearchTree::Node* t, Data * x) {
    //goes down the tree to find the data we want-recursive-returns a pointer to node(data)
    if (t == NULL)
        return NULL;
    else if (*x < *t->data)
        return find(t->left, x);
    else if (*x > *t->data)
        return find(t->right, x);
    else
        return t;

    return NULL;
}

BinarySearchTree::Node* BinarySearchTree::find(BinarySearchTree::Node* t, string key) {
    //another implementation of find cause i couldnt make it into one-xD
    //they essentially work in the same way though
    if (t == NULL)
        return NULL;
    else if (key < *t->data)
        return find(t->left, key);
    else if (key > *t->data)
        return find(t->right, key);
    else
        return t;

    return NULL;
}
//there are 4 implementations of inorder_process_data
//each time we pass the filter so we know what we need to calculate
//e.g. percentage of people without dates.
//note that all calculations are based on piazza 
//e.g. in the case of dates we ingore them in the denominator but not on the numerator
//pls check README for more info



//these functions are used to go through the corresponding tree
//beacuse there one tree implementation but many trees used (3 of them)
//we need to specify many inorder_process_data functions each one dealing with a specific type of data
void BinarySearchTree::inorder_process_data(VaccineData * vacdata) {
    inorder_process_data(root, vacdata);
}

void BinarySearchTree::inorder_process_data(SearchFilter & filter) {
    inorder_process_data(root, filter);
}

void BinarySearchTree::inorder_process_data(SearchFilterByAge & filter) {
    inorder_process_data(root, filter);
}

void BinarySearchTree::inorder_process_data(Node* t, SearchFilter & filter) {
    if (t == NULL) {
        return;
    }
    inorder_process_data(t->left, filter);


    Country * activeCountry = dynamic_cast<Country*> (t->data);
    //check for dynamic cast fail
    if (activeCountry == NULL) {
        exit(123);
    }

    Disease * activeDisease = filter.disease;

    if (activeDisease != NULL) {
        //for every country or if the country is the given country
        if ((filter.country == "" || (filter.country == activeCountry->name))) {
            SearchFilter copy = filter;
            copy.country = activeCountry->name;

            float x = activeDisease->vaccinated.count(copy);

            SearchFilter filter2 = filter;

            filter2.date1 = "";
            filter2.date2 = "";
            filter2.country = activeCountry->name;

            //count counts the number of people in the skiplists
            //obviously it goes through the last level of the skip list to achieve this
            float y1 = activeDisease->vaccinated.count(filter2);
            float y2 = activeDisease->not_vaccinated.count(filter2);
            float y = y1 + y2;
            float r;

            //numbers are caluclated based on piazza
            if (x + y == 0) {
                r = 0;
            } else {
                r = x / y;
            }

            r = r * 100;

            cout << "Country: " << activeCountry->name << ": " << x << " " << r << "%" << endl;
        }
    } else {
        cout << "Disease not found. ( BinarySearchTree::inorder_process_data)" << ":" << filter.disease->name << endl;
        exit(124);
    }


    inorder_process_data(t->right, filter);
}
//code is almost the same in all these 4 functions
//note that the calculations are different though
void BinarySearchTree::inorder_process_data(Node* t, SearchFilterByAge & filter) {
    if (t == NULL) {
        return;
    }
    inorder_process_data(t->left, filter);


    Country * activeCountry = dynamic_cast<Country*> (t->data);

    if (activeCountry == NULL) {
        exit(123);
    }

    Disease * activeDisease = filter.disease;

    if (activeDisease != NULL) {
        if ((filter.country == "" || (filter.country == activeCountry->name))) {
            SearchFilterByAge copy = filter;
            copy.country = activeCountry->name;

            float * x = activeDisease->vaccinated.count(copy);

            SearchFilterByAge filter2 = filter;

            filter2.date1 = "";
            filter2.date2 = "";
            filter2.country = activeCountry->name;

            float * y1 = activeDisease->vaccinated.count(filter2);
            float * y2 = activeDisease->not_vaccinated.count(filter2);
            float y[4];
            float r[4];
            //there are 4 group ages
            //we calculate each one seperately
            for (int i = 0; i < 4; i++) {
                y[i] = y1[i] + y2[i];
            }

            for (int i = 0; i < 4; i++) {
                if (x[i] + y[i] == 0) {
                    r[i] = 0;
                } else {
                    r[i] = x[i] / y[i];
                }

                r[i] = r[i] * 100;
            }

            cout << "Country: " << activeCountry->name << "  [ 0- 19]: " << x[0] << " " << r[0] << "%" << endl;
            cout << "Country: " << activeCountry->name << "  [ 20-39]: " << x[1] << " " << r[1] << "%" << endl;
            cout << "Country: " << activeCountry->name << "  [ 40-59]: " << x[2] << " " << r[2] << "%" << endl;
            cout << "Country: " << activeCountry->name << "  [ 60+  ]: " << x[3] << " " << r[3] << "%" << endl;

            delete [] x;
            delete [] y1;
            delete [] y2;
        }
    } else {
        cout << "Disease not found. ( BinarySearchTree::inorder_process_data)" << ":" << filter.disease->name << endl;
        exit(124);
    }


    inorder_process_data(t->right, filter);
}

void BinarySearchTree::inorder_process_data(Node* t, VaccineData * search_data) {
    if (t == NULL) {
        return;
    }
    inorder_process_data(t->left, search_data);

    Disease * activeDisease = dynamic_cast<Disease*> (t->data);

    if (activeDisease == NULL) {
        exit(1);
    }

    if (activeDisease != NULL) {
        cout << activeDisease->name << ": ";

        bool printed = false;
        {
            VaccineData * data = (VaccineData *) activeDisease->vaccinated.search(search_data);

            if (data != NULL) {
                cout << "Vaccinated at ";
                data->date.print();
                printed = true;
            }
        }
        {
            VaccineData * data = (VaccineData *) activeDisease->not_vaccinated.search(search_data);

            if (data != NULL) {
                cout << "Not vaccinated" << endl;
                printed = true;
            }
        }
        if (!printed) {
            cout << endl;
        }
    }

    inorder_process_data(t->right, search_data);
}