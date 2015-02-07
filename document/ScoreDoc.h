#ifndef SCOREDOC_H_INCLUDED
#define SCOREDOC_H_INCLUDED
#include <iostream>
using namespace std;

class ScoreDoc {
public:
    int doc;
    ScoreDoc(int docID) {
        doc = docID;
    }

};

#endif // SCOREDOC_H_INCLUDED
