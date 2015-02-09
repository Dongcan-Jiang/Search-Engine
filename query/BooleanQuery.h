#ifndef BOOLEANQUERY_H_INCLUDED
#define BOOLEANQUERY_H_INCLUDED
#include "Query.h"
#include "../document/IndexSearcher.h"
#include "../scorer/ConjunctionScorer.h"
#include "../scorer/DisjunctionScorer.h"
#include "../scorer/ReqExclScorer.h"
#include "../scorer/ReqOptScorer.h"
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
        if(scorers[MUST].empty()&&scorers[SHOULD].empty()) {
            ifstream &fin = is.iindexIfstream.iindexPostinglist;
            return make_shared<TermScorer>(fin, 0, 0, 0);
        }
        if(scorers[MUST].empty()) {
            if(scorers[MUST_NOT].empty())
                return make_shared<DisjunctionScorer>(scorers[SHOULD]);
            else
                return make_shared<ReqExclScorer>(make_shared<DisjunctionScorer>(scorers[SHOULD]), make_shared<DisjunctionScorer>(scorers[MUST_NOT]));
        }
        if(scorers[SHOULD].empty()) {
            if(scorers[MUST_NOT].empty())
                return make_shared<ConjunctionScorer>(scorers[MUST]);
            else
                return make_shared<ReqExclScorer>(make_shared<ConjunctionScorer>(scorers[MUST]), make_shared<DisjunctionScorer>(scorers[MUST_NOT]));
        }
        if(scorers[MUST_NOT].empty()) {
            return make_shared<ReqOptScorer>(make_shared<ConjunctionScorer>(scorers[MUST]), make_shared<DisjunctionScorer>(scorers[SHOULD]));
        }
        return make_shared<ReqOptScorer>(make_shared<ReqExclScorer>(make_shared<ConjunctionScorer>(scorers[MUST]), make_shared<DisjunctionScorer>(scorers[MUST_NOT])), make_shared<DisjunctionScorer>(scorers[SHOULD]));
    }

    string toString() {
        string s;
        for(auto m : bq[MUST]){
            s += "+";
            s += "(";
            s += m->toString();
            s += ") ";
        }
        for (auto m : bq[MUST_NOT]) {
            s += "-";
            s += "(";
            s += m->toString();
            s += ") ";
        }
        for (auto m : bq[SHOULD]) {
            s += "(";
            s += m->toString();
            s += ") ";
        }
        return s;
    }
    ~BooleanQuery(){}
};



#endif // BOOLEANQUERY_H_INCLUDED
