#ifndef CONJUNCTIONSCORER_H_INCLUDED
#define CONJUNCTIONSCORER_H_INCLUDED

class ConjunctionScorer: public Scorer{
public:
    int scost;
    vector<shared_ptr<Scorer>> scorers;
    bool cmp(shared_ptr<Scorer> s1, shared_ptr<Scorer> s2) {
        return s1->cost() < s2->cost();
    }
    ConjunctionScorer(vector<shared_ptr<Scorer>> & scorers){
        assert(scorers.size() > 1);
        this->scorers = scorers;
        docID = -1;
        sort(scorers.begin(), scorers.end, cmp);
        scost = scorers[0]->cost();
    }
    int doc() {
        return docID;
    }
    int score() {}
    int next() {
        auto iter = scorers[0]; //如果用迭代器的话指针的指针要怎么取值？
        while(iter->next() < DOC_EXHAUSTED) {
            int docid = iter->doc();
            int i = 1;
            for(i = 1; i<scorers.size(); i++) {
                if(scorers[i]->doc() != docid){
                    if(scorers[i]->advance(docid) != docid)
                        break;
                }
            }
            if(scorers[i]->doc == DOC_EXHAUSTED)
                break;
            if(i == scorers.size())
                return iter->doc();
        }
        return DOC_EXHAUSTED;
    }

    int cost() {
        return scost;
    }
    ~TermScorer() {}

};


#endif // CONJUNCTIONSCORER_H_INCLUDED
