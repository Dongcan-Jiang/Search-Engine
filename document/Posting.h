#ifndef POSTING_H_INCLUDED
#define POSTING_H_INCLUDED

#include <vector>
#include <iostream>
using namespace std;
class Posting {
public:
    int docID;
    vector<int> position;
    Posting(int docID, const vector<int> &position) {
        this->docID = docID;
        this->position = position;
    }
    string toString() {
        string s = "<"+to_string(docID)+"("+to_string(position.size())+")"+": ";
        for (size_t i = 0; i+1 < position.size(); i++) {
            s += to_string(position[i]);
            s += ", ";
        }
        s += to_string(position.back());
        s += ">";
        return s;
    }
};

#endif // POSTING_H_INCLUDED
