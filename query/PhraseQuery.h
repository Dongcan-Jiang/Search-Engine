#ifndef PHRASEQUERY_H_INCLUDED
#define PHRASEQUERY_H_INCLUDED

#include "TermQuery.h"
#include "../scorer/PhraseScorer.h"
class PhraseQuery: public Query{
public:
    vector<shared_ptr<TermQuery>> v;
    int dis;
    PhraseQuery(const vector<shared_ptr<TermQuery>> &v, int dis = 5) {
        this->v = v;
        this->dis = dis;
    }
    void setDis(int dis){
        this->dis = dis;
    }

    shared_ptr<Scorer> getScorer(IndexSearcher &is) {
        shared_ptr<PhraseScorer> ps = make_shared<PhraseScorer>(is, v, dis);
        return ps;
    }

    string toString() {
        string s;
        for(size_t i = 0; i < v.size(); i++) {
            s += v[i]->toString();
            s += " ";
        }
        s += "~" + to_string(dis);
        return s;
    }

};

#endif // PHRASEQUERY_H_INCLUDED
