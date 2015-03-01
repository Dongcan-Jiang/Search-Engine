#ifndef SCORER_H_INCLUDED
#define SCORER_H_INCLUDED

#include <cassert>
#include <climits>
#include "../debug/SeDebug.h"

class Scorer {
public:
    static const int DOC_EXHAUSTED = INT_MAX;
    int docID = -1;
    int scost;
    int docScore = 0;
    //to get docID
    virtual int doc() {
        return docID;
    }
    //to get doc score
    virtual int score() = 0;
    //move to next doc, unpredictable when scorer's current docID == DOC_EXHAUSTED
    virtual int next() = 0;
    //to get cost
    virtual int cost(){
        return scost;
    }
    //0 <= doc < DOC_EXHAUSTED, unpredictable when scorer's current docID >= doc.
    virtual int advance(int doc) {
        #ifdef _DEBUG_ADVANCE_
        assert(docID < doc);
        #endif
        while(next() < doc);
        return docID;
    }

    virtual ~Scorer() {}

};

#endif // SCORER_H_INCLUDED
