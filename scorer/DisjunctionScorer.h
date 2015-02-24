#ifndef DISJUNCTIONSCORER_H_INCLUDED
#define DISJUNCTIONSCORER_H_INCLUDED

#include "Scorer.h"

class DisjunctionScorer: public Scorer{
public:
    vector<shared_ptr<Scorer>> scorers;

    static bool greaterDocID (shared_ptr<Scorer> a, shared_ptr<Scorer> b) {
        return b->doc() < a->doc();
    };

    DisjunctionScorer(const vector<shared_ptr<Scorer>> & sv) {
        assert(sv.size() > 0);
        for(auto s : sv){
            if(s->next() < DOC_EXHAUSTED)
                scorers.push_back(s);
        }
        make_heap(scorers.begin(), scorers.end(), greaterDocID);
        scost = 0;
        for(auto s : scorers) {
            scost += s->cost();
        }
    }

    int score() {return{};}

    int next() {
        int minID;
        if(scorers.size() == 0)
            return docID = DOC_EXHAUSTED;
        minID = scorers[0]->doc();
        do{
            shared_ptr<Scorer> sc = scorers[0];
            pop_heap(scorers.begin(), scorers.end(), greaterDocID);
            scorers.pop_back();
            if(sc->next() < DOC_EXHAUSTED) {
                scorers.push_back(sc);
                push_heap(scorers.begin(), scorers.end(), greaterDocID);
            }
        }while(scorers.size() !=0 && scorers[0]->doc() == minID);
        return docID = minID;
    }

    int advance(int doc) {
        assert(docID < doc);
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

#endif // DISJUNCTIONSCORER_H_INCLUDED
