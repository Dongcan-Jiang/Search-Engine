#ifndef TEXTFIELD_H_INCLUDED
#define TEXTFIELD_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;
class TextField {
public:
    string text;
    TextField(const string &s) {
        text = s;
    }
};

#endif // TEXTFIELD_H_INCLUDED
