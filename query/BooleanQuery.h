#ifndef BOOLEANQUERY_H_INCLUDED
#define BOOLEANQUERY_H_INCLUDED
#include "Query.h"
#include "../document/IndexSearcher.h"
#include "../scorer/ConjunctionScorer.h"
#include "../scorer/DisjunctionScorer.h"
class BooleanQuery: public Query{
public:
    static const int MUST = 0;
    static const int SHOULD = 1;
    static const int MUST_NOT = 2;
    static const int NUM_OF_TYPES = 3;
    vector<shared_ptr<Query>> bq[NUM_OF_TYPES];
    void add(int type, shared_ptr<Query> q){
        bq[type].push_back(q);
    }

    shared_ptr<Scorer> getScorer(IndexSearcher &is){
        vector<shared_ptr<Scorer>> scorers[NUM_OF_TYPES];
        for(int i = 0; i < NUM_OF_TYPES; i++) {
            for(auto q : bq[i])
                scorers[i].push_back(q->getScorer(is));
        }
        if(scorers[SHOULD].empty()&&scorers[MUST_NOT].empty())
            return make_shared<ConjunctionScorer> (scorers[MUST]);
        if(scorers[MUST].empty()&&scorers[MUST_NOT].empty())
            return make_shared<DisjunctionScorer> (scorers[SHOULD]);
    }
    ~BooleanQuery(){}
};



#endif // BOOLEANQUERY_H_INCLUDED
