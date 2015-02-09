#ifndef TERMQUERY_H_INCLUDED
#define TERMQUERY_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;
#include "Query.h"
#include "../document/IndexSearcher.h"
#include "../scorer/TermScorer.h"

class TermQuery: public Query{
public:
    string term;

    TermQuery(const string &item){
        term = item;
    }

    shared_ptr<Scorer> getScorer(IndexSearcher &is){
        ifstream &fin = is.iindexIfstream.iindexPostinglist;
        int termID = is.iindexIfstream.fetchTermID(term);
        if(termID == -1) {
            return make_shared<TermScorer>(fin, 0, 0, 0);
        }
        int begin = is.iindexIfstream.getPostinglistBegin(termID);
        int end = is.iindexIfstream.getPostinglistEnd(termID);
        int df = is.iindexIfstream.getDF(termID);
        shared_ptr<TermScorer> ts = make_shared<TermScorer>(fin, begin, end, df);
        return ts;
    }

    string toString() {
        return term;
    }

    ~TermQuery(){}
};

#endif // TERMQUERY_H_INCLUDED
