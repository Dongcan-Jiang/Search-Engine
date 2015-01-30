#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include <memory>
#include <map>
#include <string>
#include <iostream>
using namespace std;
#include "TextField.h"
#include "StoredField.h"

class Document {
public:
    shared_ptr<TextField> textField;
    map<string, shared_ptr<StoredField>>storedfield;
    void setTextField(shared_ptr<TextField> textf) {textField = textf;}
    void addStoredField(shared_ptr<StoredField> storedf) {}
    shared_ptr<StoredField> getStoredField(const string &fieldName) {return {};}
};

#endif // DOCUMENT_H_INCLUDED
