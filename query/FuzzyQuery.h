#ifndef FUZZYQUERY_H_INCLUDED
#define FUZZYQUERY_H_INCLUDED

#include "TermQuery.h"
#include "../scorer/FuzzyScorer.h"

class FuzzyQuery: public TermQuery {
public:
    static const int FUZZY_THRESHOLD = 2;
    FuzzyQuery(const string &item): TermQuery(item){}

    shared_ptr<Scorer> getScorer(IndexSearcher &is){
        vector<shared_ptr<TermScorer>> fts;
        fetchTerm(is, fts);
        if (fts.size() == 0)
            return make_shared<TermScorer>(is.iindexIfstream.iindexPostinglist, 0, 0, 0);
        else
            return make_shared<FuzzyScorer>(fts);
    }

    bool fetchTerm(IndexSearcher &is, vector<shared_ptr<TermScorer>> &fts) {
        int low = 0;
        int high = is.iindexIfstream.TERM_NUM-1;
        int mid;
        int PREFIX_NUM = 2;
        string s;
        string termPrefix = term.substr(0, PREFIX_NUM);
        while (high >= low) {
            mid = (low+high)/2;
            s = is.iindexIfstream.getTerm(mid);
            s = s.substr(0, PREFIX_NUM);
            if (s > termPrefix)
                high = mid - 1;
            else {
                if (s < termPrefix)
                    low = mid + 1;
                else {
                    int lowerbound = mid-1;
                    int upperbound = mid+1;
                    filterDistance(is, mid, fts);
                    while(lowerbound != -1 && is.iindexIfstream.getTerm(lowerbound).substr(0,PREFIX_NUM) == termPrefix){
                        filterDistance(is, lowerbound, fts);
                        lowerbound--;
                    }
                    //lowerbound++;
                    while(upperbound != is.iindexIfstream.TERM_NUM && is.iindexIfstream.getTerm(upperbound).substr(0, PREFIX_NUM) == termPrefix) {
                        filterDistance(is, upperbound, fts);
                        upperbound++;
                    }
                    return true;
                }
            }
        }
        return false;
    }


    void filterDistance(IndexSearcher &is, int i, vector<shared_ptr<TermScorer>> &fts) {
        string s = is.iindexIfstream.getTerm(i);
        //test
        //cout<<s<<" ";
        if (abs((int)s.size()-(int)term.size()) <= FUZZY_THRESHOLD && util::editDistance(s, term) <= FUZZY_THRESHOLD) {
            int begin = is.iindexIfstream.getPostinglistBegin(i);
            int end = is.iindexIfstream.getPostinglistEnd(i);
            int df = is.iindexIfstream.getDF(i);
            shared_ptr<TermScorer> ts = make_shared<TermScorer>(is.iindexIfstream.iindexPostinglist, begin, end, df);
            fts.push_back(ts);

            //test
            //cout<<"(choose:)"<<s<<" ";
        }
    }
};

#endif // FUZZYQUERY_H_INCLUDED
