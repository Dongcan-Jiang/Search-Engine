#ifndef CONJUNCTIONSCORER_H_INCLUDED
#define CONJUNCTIONSCORER_H_INCLUDED
#include <algorithm>

#include "Scorer.h"

class ConjunctionScorer: public Scorer{
public:
    vector<shared_ptr<Scorer>> scorers;

    ConjunctionScorer(const vector<shared_ptr<Scorer>> & s) {
        assert(s.size() > 0);
        this->scorers = s;
        sort(scorers.begin(), scorers.end(),
                [](shared_ptr<Scorer> s1, shared_ptr<Scorer> s2){
                    return s1->cost() < s2->cost();
                }
        );
        scost = scorers[0]->cost();
    }

    int score() {return{};}

    int findNext(shared_ptr<Scorer> iter) {
        while(iter->doc() < DOC_EXHAUSTED) {
            int docid = iter->doc();
            size_t i;
            for(i = 1; i < scorers.size(); i++) {
                if(scorers[i]->doc() < docid){
                    if(scorers[i]->advance(docid) > docid)
                        break;
                }
            }
            if(i == scorers.size())
                return docID = iter->doc();
            if(scorers[i]->doc() == DOC_EXHAUSTED)
                break;
            iter->advance(scorers[i]->doc());
        }
        return docID = DOC_EXHAUSTED;
    }

    int next() {
        auto iter = scorers[0];
        iter->next();
        return findNext(iter);
    }

    int advance(int doc) {
        assert(docID < doc);
        scorers[0]->advance(doc);
        return findNext(scorers[0]);
    }

};


#endif // CONJUNCTIONSCORER_H_INCLUDED
