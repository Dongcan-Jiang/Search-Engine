#ifndef FUZZYSCORER_H_INCLUDED
#define FUZZYSCORER_H_INCLUDED

#include "PositionAbleScorer.h"

class FuzzyScorer: public PositionAbleScorer {
public:
    vector<shared_ptr<TermScorer>> fts;
    FuzzyScorer(const vector<shared_ptr<TermScorer>> & fts) {
        this->fts = fts;
    }


};


#endif // FUZZYSCORER_H_INCLUDED
