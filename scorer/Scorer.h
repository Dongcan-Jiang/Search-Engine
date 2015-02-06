#ifndef SCORER_H_INCLUDED
#define SCORER_H_INCLUDED

class Scorer {
public:
    static const int DOC_EXHAUSTED = INT_MAX;
    int docID = -1;
    int scost;
    virtual int doc() = 0;
    virtual int score() = 0;
    virtual int next() = 0;
    int advance(int doc) {
        while(next() < doc);
        return docID;
    }
    virtual int cost() = 0;
    virtual ~Scorer() {}

};

#endif // SCORER_H_INCLUDED
