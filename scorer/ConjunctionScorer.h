#ifndef CONJUNCTIONSCORER_H_INCLUDED
#define CONJUNCTIONSCORER_H_INCLUDED
#include <algorithm>

class ConjunctionScorer: public Scorer{
public:
    vector<shared_ptr<Scorer>> scorers;
    ConjunctionScorer(vector<shared_ptr<Scorer>> & scorers) {
        assert(scorers.size() > 1);
        this->scorers = scorers;
        sort(scorers.begin(), scorers.end(),
                [](shared_ptr<Scorer> s1, shared_ptr<Scorer> s2){
                    return s1->cost() < s2->cost();
                }
        );
        scost = scorers[0]->cost();
    }
    int score() {}
    int next() {
        auto iter = scorers[0];
        iter->next();
        while(iter->doc() < DOC_EXHAUSTED) {
            int docid = iter->doc();
            size_t i;
            for(i = 1; i < scorers.size(); i++) {
                if(scorers[i]->doc() < docid){
                    if(scorers[i]->advance(docid) > docid)
                        break;
                }
            }
            if(scorers[i]->doc() == DOC_EXHAUSTED)
                break;
            if(i == scorers.size())
                return docID = iter->doc();
            iter->advance(scorers[i]->doc());
        }
        return docID = DOC_EXHAUSTED;
    }

    int cost() {
        return scost;
    }
    ~ConjunctionScorer() {}

};


#endif // CONJUNCTIONSCORER_H_INCLUDED
