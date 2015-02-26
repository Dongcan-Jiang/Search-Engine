#ifndef FUZZYQUERY_H_INCLUDED
#define FUZZYQUERY_H_INCLUDED

#include "TermQuery.h"

class FuzzyQuery: public TermQuery {
public:
    string fuzzyTerm;
    int lowerbound = -1;
    int upperbound = -1;

    FuzzyQuery(const string &item){
        fuzzyTerm = item;
    }

    shared_ptr<Scorer> getScorer(IndexSearcher &is){
        fetchTermID(is);
        return fs = make_shared<FuzzyScorer>(is, lowerbound, upperbound);
    }

    bool fetchTermID(IndexSearcher &is) {
        int low = 0;
        int high = is.iindexIfstream.TERM_NUM-1;
        int mid;
        string s;
        int fsize = fuzzyTerm.size();
        while (high >= low) {
            mid = (low+high)/2;
            s = is.iindexIfstream.getTerm(mid);
            s = substr(0, fsize);
            if (s > fuzzyTerm)
                high = mid - 1;
            else {
                if (s < fuzzyTerm)
                    low = mid + 1;
                else {
                    lowerbound = mid-1;
                    upperbound = mid+1;
                    while(lowerbound != -1 && is.iindexIfstream.getTerm(lowerbound).substr(0,fsize) == fuzzyTerm){
                        lowerbound--;
                    }
                    lowerbound++;
                    while(upperbound != is.iindexIfstream.TERM_NUM && is.iindexIfstream.getTerm(upperbound).substr(0,fsize) == fuzzyTerm) {
                        upperbound++;
                    }
                    return true;
                }
            }
        }
        return false;
    }


};

#endif // FUZZYQUERY_H_INCLUDED
