#ifndef FUZZYQUERY_H_INCLUDED
#define FUZZYQUERY_H_INCLUDED

#include "TermQuery.h"

class FuzzyQuery: public TermQuery {
public:
    int lowerbound = -1;
    int upperbound = -1;
    vector<shared_ptr<TermScorer>> fts;
    static const int FUZZY_THRESHOLD = 2;
    FuzzyQuery(const string &item): TermQuery(item){}

    shared_ptr<Scorer> getScorer(IndexSearcher &is){
        fetchTermID(is);
        for(int i = lowerbound; i < upperbound; i++) {
            if(editDistance(is.iindexIfstream.getTerm(i), term) <= FUZZY_THRESHOLD) {
                int begin = is.iindexIfstream.getPostinglistBegin(i);
                int end = is.iindexIfstream.getPostinglistEnd(i);
                int df = is.iindexIfstream.getDF(i);
                shared_ptr<TermScorer> ts = make_shared<TermScorer>(fin, begin, end, df);
                fts.push_back(ts);
            }
        }
        return fs = make_shared<FuzzyScorer>(fts);
    }

    bool fetchTermID(IndexSearcher &is) {
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
                    lowerbound = mid-1;
                    upperbound = mid+1;
                    while(lowerbound != -1 && is.iindexIfstream.getTerm(lowerbound).substr(0,PREFIX_NUM) == termPrefix){
                        lowerbound--;
                    }
                    lowerbound++;
                    while(upperbound != is.iindexIfstream.TERM_NUM && is.iindexIfstream.getTerm(upperbound).substr(0, PREFIX_NUM) == termPrefix) {
                        upperbound++;
                    }
                    return true;
                }
            }
        }
        return false;
    }

    int editDistance(const string &s1; const string &s2) {
        int l1 = s1.size()+1;
        int l2 = s2.size()+1;
        int dis[l1][l2];
        for (int i = 0; i < l1; i++) {
            dis[i][0] = i;
        }
        for (int j = 0; j < l2; j++) {
            dis[0][j] = j;
        }
        for (int i = 1 ; i< l1; i++) {
            for (int j = 1;  j< l2; j++) {
                int k = 1;
                if (s1[i-1] == s1[j-1])
                    k = 0;
                dis[i][j] = min(min(dis[i-1][j]+1, dis[i][j-1]+1), dis[i-1][j-1]+k);
            }
        }
        return dis[l1-1][l2-1];
    }

};

#endif // FUZZYQUERY_H_INCLUDED
