#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>

#include "SearchFilter.h"

using namespace std;

//abstract class used to organise code
//e.g. in tree struct we pass Data type to be able to store any kind of data (tree of citizens,diseases and countries)
//this way we dont need to copy code thrice essentially having three implementations of a tree

class Data {
public:
    Data();
    Data(const Data& orig);
    virtual ~Data();

    //all functions are overloaded and used on the corresponding type
    //more on overloading on README
    virtual bool operator<(const Data& right) const = 0;
    virtual bool operator>(const Data& right) const = 0;
    virtual bool operator==(const Data& right) const;
    virtual bool operator==(const SearchFilter & filter) const;

    virtual void print(ostream & out) const = 0;
    
    virtual int compare(const string key) const = 0; // 0:equal, -1:data<key +1:data > key

    friend ostream & operator<<(ostream & left, const Data &right);
    
    friend bool operator<(const string& left, const Data &right);
    friend bool operator<(const Data &left, const string& right);
    friend bool operator>(const string& left, const Data &right);
    friend bool operator>(const Data &left, const string& right);
    friend bool operator==(const string& left, const Data &right);
    friend bool operator==(const Data &left, const string& right);
private:

};


#endif /* DATA_H */

