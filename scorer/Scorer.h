#ifndef SCORER_H_INCLUDED
#define SCORER_H_INCLUDED

class Scorer {
public:
    static const int DOC_EXHAUSTED = INT_MAX;
    int docID = -1;
    int scost;
    int docScore = 0;
    virtual int doc() {
        return docID;
    }

    virtual int score() = 0;

    virtual int next() = 0;

    virtual int cost(){
        return scost;
    }

    virtual int advance(int doc) {
        while(next() < doc);
        return docID;
    }

    virtual ~Scorer() {}

};

#endif // SCORER_H_INCLUDED
