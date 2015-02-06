#ifndef DISJUNCTIONSCORER_H_INCLUDED
#define DISJUNCTIONSCORER_H_INCLUDED

class scorerDocID{
public:
    int scorerID;
    int preDocID;
    scorerDocID(int s, int d) {
        scorerID = s;
        preDocID = d;
    }
};

class DisjunctionScorer: public Scorer{
public:
    vector<shared_ptr<Scorer>> scorers;
    vector<scorerDocID> sdHeap;
    DisjunctionScorer(vector<shared_ptr<Scorer>> & scorers) {
        assert(scorers.size() > 1);
        this->scorers = scorers;
        for(size_t i = 0; i < scorers.size(); i++) {
            if(scorers[i]->next() < DOC_EXHAUSTED) {
                sdHeap.push_back(scorerDocID(i,scorers[i]->doc()));
            }
        }
        make_heap(sdHeap.begin(), sdHeap.end(),
                    [](scorerDocID &a, scorerDocID &b) {
                        return b.preDocID < a.preDocID;
                    }
        );
    }
    int score() {}
    int next() {
        int minID = sdHeap[0].preDocID;
        if(sdHeap.size() == 0)
            return docID = DOC_EXHAUSTED;
        do{
            int sc = sdHeap[0].scorerID;
            pop_heap(sdHeap.begin(), sdHeap.end(),
                        [](scorerDocID &a, scorerDocID &b) {
                            return b.preDocID < a.preDocID;
                        }
            );
            sdHeap.pop_back();
            if(scorers[sc]->next() < DOC_EXHAUSTED) {
                sdHeap.push_back(scorerDocID(sc,scorers[sc]->doc()));
                push_heap(sdHeap.begin(), sdHeap.end(),
                        [](scorerDocID &a, scorerDocID &b) {
                            return b.preDocID < a.preDocID;
                        }
                );
            }
        }while(sdHeap.size() !=0 && sdHeap[0].preDocID == minID);
        return docID = minID;
    }

    int cost() {
        scost = 0;
        for(auto s : scorers) {
            scost += s->cost();
        }
        return scost;
    }
    ~DisjunctionScorer() {}

};

#endif // DISJUNCTIONSCORER_H_INCLUDED
