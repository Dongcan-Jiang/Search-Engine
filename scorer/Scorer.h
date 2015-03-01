#ifndef SCORER_H_INCLUDED
#define SCORER_H_INCLUDED

#include <climits>

class Scorer {
public:
    static const int DOC_EXHAUSTED = INT_MAX;
    int docID = -1;
    int scost;
    int docScore = 0;
    int doc() {
        return docID;
    }

    virtual int score() = 0;

    virtual int next() = 0;

    int cost(){
        return scost;
    }

    int advance(int doc) {
        while(next() < doc);
        return docID;
    }

    virtual ~Scorer() {}

};

#endif // SCORER_H_INCLUDED
