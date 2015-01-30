#ifndef STOREDFIELD_H_INCLUDED
#define STOREDFIELD_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;
class StoredField {
public:
    string fieldName;
    string stored;
    StoredField(const string &fieldName, const string &stored) {
        this->fieldName = fieldName;
        this->stored = stored;
    }
    string stringValue() {return stored;}
};

#endif // STOREDFIELD_H_INCLUDED
