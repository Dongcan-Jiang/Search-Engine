#ifndef DISJUNCTIONSCORER_H_INCLUDED
#define DISJUNCTIONSCORER_H_INCLUDED


class DisjunctionScorer: public Scorer{
public:
    vector<shared_ptr<Scorer>> scorers;
    static bool greaterDocID (shared_ptr<Scorer> a, shared_ptr<Scorer> b) {
        return b->doc() < a->doc();
    };

    DisjunctionScorer(vector<shared_ptr<Scorer>> & scorers) {
        assert(scorers.size() > 1);
        this->scorers = scorers;
        scost = 0;
        for(auto s : scorers) {
            scost += s->cost();
        }
        for(auto s : scorers)
            s->next();
        make_heap(scorers.begin(), scorers.end(), greaterDocID);
    }
    int score() {}
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

    int cost() {
        return scost;
    }
    ~DisjunctionScorer() {}

};

#endif // DISJUNCTIONSCORER_H_INCLUDED