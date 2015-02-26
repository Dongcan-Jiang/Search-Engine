#ifndef FUZZYSCORER_H_INCLUDED
#define FUZZYSCORER_H_INCLUDED

#include "PositionAbleScorer.h"

class FuzzyScorer: public PositionAbleScorer {
public:
    istream &in;
    int lowerbound;
    int upperbound;
    int offset;

    FuzzyScorer(istream &fin, int lowerbound, int upperbound):in(fin){
        this->lowerbound = lowerbound;
        this->upperbound = upperbound;
    }



};


#endif // FUZZYSCORER_H_INCLUDED
