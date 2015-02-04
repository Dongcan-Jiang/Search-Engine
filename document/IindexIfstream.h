#ifndef IINDEXIFSTREAM_H_INCLUDED
#define IINDEXIFSTREAM_H_INCLUDED

#include <stdlib.h>
#include <cassert>
#include "Posting.h"

class IindexIfstream {
public:
    ifstream iindexTable,iindexTerm,iindexPostinglist;
    static const int ROW_LENGTH = sizeof(int)*3;
    int TERM_NUM;

    IindexIfstream(const string &indexDir) {
        iindexTable.open(indexDir+"/"+"indextable", ios::binary);
        assert(iindexTable);
        iindexTerm.open(indexDir+"/"+"indexterm", ios::binary);
        assert(iindexTerm);
        iindexPostinglist.open(indexDir+"/"+"indexpostinglist", ios::binary);
        assert(iindexPostinglist);

        TERM_NUM = iindexTable.seekg(0,ios::end).tellg()/ROW_LENGTH;
    }

    string getTerm(int termID) {
        int address;
        string term;
        iindexTable.seekg(ROW_LENGTH*termID).read((char*)&address,sizeof(address));
        getline(iindexTerm.seekg(address),term,'\0');
        return term;
    }

    int getPostinglistBegin(int termID) {
        int address;
        iindexTable.seekg(ROW_LENGTH*termID+sizeof(int)).read((char*)&address,sizeof(address));
        return address;

        //getline(iindexPostinglist.seekg(address),postingList,'\0');
        //return postingList;
    }

    int getDF(int termID) {
        int df;
        iindexTable.seekg(ROW_LENGTH*termID+2*sizeof(int)).read((char*)&df,sizeof(df));
        return df;
    }

    string toString(int termID) {
        string s;
        iindexPostinglist.seekg(getPostinglistBegin(termID));
        int df = getDF(termID);
        for (int i = 0; i < df; i++) {
            Posting p(iindexPostinglist);
            s += p.toString();
            s += " ";
        }
        return s;
    }

    string toString() {
        string s;
        for (int i = 0; i < TERM_NUM; i++) {
            s += getTerm(i);
            s += ":";
            s += toString(i);
            s += "\n";
        }
        return s;
    }

    void close() {
        iindexTable.close();
        iindexTerm.close();
        iindexPostinglist.close();
    }

    int fetchTermID(const string &term) {
        int low = 0;
        int high = TERM_NUM-1;
        int mid;
        string s;
        while (high >= low) {
            mid = (low+high)/2;
            s = getTerm(mid);
            if (s > term)
                high = mid - 1;
            else {
                if (s < term)
                    low = mid + 1;
                else
                    return mid;
            }
        }
        return -1;
    }

};

#endif // IINDEXIFSTREAM_H_INCLUDED
