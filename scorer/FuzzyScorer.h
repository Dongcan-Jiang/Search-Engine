#ifndef FUZZYSCORER_H_INCLUDED
#define FUZZYSCORER_H_INCLUDED

#include "PositionAbleScorer.h"

class FuzzyScorer: public PositionAbleScorer {
public:
    vector<shared_ptr<TermScorer>> scorers;

    static bool greaterDocID (shared_ptr<Scorer> a, shared_ptr<Scorer> b) {
        return b->doc() < a->doc();
    };

    FuzzyScorer(const vector<shared_ptr<TermScorer>> & fts) {
        scorers = fts;
        assert(fts.size() > 0);
        for(auto s : fts){
            if(s->next() < DOC_EXHAUSTED)
                scorers.push_back(s);
        }
        make_heap(scorers.begin(), scorers.end(), greaterDocID);
        scost = 0;
        for(auto s : scorers) {
            scost += s->cost();
        }
    }
    int next() {return{};}
    int score() {return{};}
    vector<int> getPosition() {return{};}


};


#endif // FUZZYSCORER_H_INCLUDED
