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
    Posting(istream& in) {
        in.read((char*)&docID, sizeof(docID));
        int n;
        in.read((char*)&n, sizeof(n));
        int p;
        for (int i = 0; i< n; i++) {
            in.read((char*)&p, sizeof(p));
            position.push_back(p);
        }
    }
    void writeTo(ostream& out){
        int size = 0;
        out.write((char*) &docID, sizeof(docID));
        size = (int)position.size();
        out.write((char*) &size, sizeof(size));
        for (size_t i = 0; i < position.size(); i++)
            out.write((char*) &position[i], sizeof(position[i]));
    }

    string toString() {
        string s = "<"+to_string(docID)+"("+to_string(position.size())+")"+": ";
        for (size_t i = 0; i+1 < position.size(); i++) {
            s += to_string(position[i]);
            s += ", ";
        }
        if(position.size() != 0)
            s += to_string(position.back());
        s += ">";
        return s;
    }


};

#endif // POSTING_H_INCLUDED
