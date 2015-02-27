#ifndef FUZZYSCORER_H_INCLUDED
#define FUZZYSCORER_H_INCLUDED

#include "PositionAbleScorer.h"
#include <set>

class FuzzyScorer: public PositionAbleScorer {
public:
    vector<shared_ptr<TermScorer>> scorers;
    vector<int> preOffset;

    static bool greaterDocID (shared_ptr<Scorer> a, shared_ptr<Scorer> b) {
        return b->doc() < a->doc();
    };

    FuzzyScorer(const vector<shared_ptr<TermScorer>> & fts) {
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

    int next() {
        int minID;
        preOffset.clear();
        if(scorers.size() == 0)
            return docID = DOC_EXHAUSTED;
        minID = scorers[0]->doc();
        do{
            shared_ptr<TermScorer> sc = scorers[0];
            pop_heap(scorers.begin(), scorers.end(), greaterDocID);
            scorers.pop_back();
            preOffset.push_back(sc->offset);
            if(sc->next() < DOC_EXHAUSTED) {
                scorers.push_back(sc);
                push_heap(scorers.begin(), scorers.end(), greaterDocID);
            }
        }while(scorers.size() !=0 && scorers[0]->doc() == minID);
        return docID = minID;
    }

    int score() {return{};}

    vector<int> getPosition() {
        set<int> pos;
        scorers[0]->getPostition(pos, preOffset);
        vector<int> vpos;
        for(auto p : pos)
            vpos.push_back(p);
        return vpos;
    }

    int advance(int doc) {
        #ifdef _DEBUG_ADVANCE_
        assert(docID < doc);
        #endif
        for (size_t i = 0; i < scorers.size(); i++) {
            if (scorers[i]->doc() < doc)
                scorers[i]->advance(doc);
        }
        int i = 0;
        int j = scorers.size()-1;
        while (i<j) {
            if (scorers[i]->doc() == DOC_EXHAUSTED) {
                while((j > i+1) && (scorers[j]->doc() == DOC_EXHAUSTED))
                    j--;
                if (scorers[j]->doc() == DOC_EXHAUSTED)
                    break;
                swap(scorers[i],scorers[j]);
            }
            i++;
        }
        if(scorers[i]->doc() == DOC_EXHAUSTED)
            scorers.resize(i);
        make_heap(scorers.begin(), scorers.end(), greaterDocID);
        return next();
    }


};


#endif // FUZZYSCORER_H_INCLUDED
