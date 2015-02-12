#ifndef PHRASESCORER_H_INCLUDED
#define PHRASESCORER_H_INCLUDED

#include "TermScorer.h"

class PhraseScorer: public Scorer{
public:
    vector<shared_ptr<TermScorer>> ts;
    int dis;
    PhraseScorer(IndexSearcher &is, const vector<shared_ptr<TermQuery>> &v, int dis) {
        assert(v.size() > 0 && dis >= 0);
        for(size_t i = 0; i < v.size(); i++)
            ts.push_back(dynamic_pointer_cast<TermScorer>(v[i]->getScorer(is)));
        this->dis = dis;
        scost = ts[0]->cost();
    }

    int score() {return{};}

    vector<int> mergePosition(const vector<int> &v1, const vector<int> &v2) {
        int p1 = 0;
        int p2 = 0;
        vector<int> v;
        int s1 = v1.size();
        int s2 = v2.size();
        while(p1 <s1 && p2 < s2){
            int d = v1[p1]+1-v2[p2];
            if(d < -dis){
                p1++;
            }else if(d <= dis){
                v.push_back(v2[p2]);
                p2++;
            }else{
                p2++;
            }
        }
        return v;
    }

    int findDoc() {
        auto iter = ts[0];
        iter->next();
        while(iter->doc() < DOC_EXHAUSTED) {
            int docid = iter->doc();
            size_t i;
            for(i = 1; i < ts.size(); i++) {
                if(ts[i]->doc() < docid){
                    if(ts[i]->advance(docid) > docid)
                        break;
                }
            }
            if(i == ts.size())
                return docID = iter->doc();
            if(ts[i]->doc() == DOC_EXHAUSTED)
                break;
            iter->advance(ts[i]->doc());
        }
        return docID = DOC_EXHAUSTED;
    }

    int next() {
        while(findDoc()!=DOC_EXHAUSTED){
            vector<int> v1 = ts[0]->getPosition();
            vector<int> v2;
            for(size_t i = 1; i < ts.size(); i++){
                v2 = ts[i]->getPosition();
                v1 = mergePosition(v1,v2);
                if(v1.size()==0)
                    break;
            }
            if(v1.size()!=0)
                return docID;
        }
        return DOC_EXHAUSTED;
    }

};


#endif // PHRASESCORER_H_INCLUDED
