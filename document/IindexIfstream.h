#ifndef IINDEXIFSTREAM_H_INCLUDED
#define IINDEXIFSTREAM_H_INCLUDED

#include <stdlib.h>
#include <cassert>
#include "Posting.h"
class IindexIfstream {
public:
    ifstream iindexTable,iindexTerm,iindexPostinglist;
    const int rowLength = sizeof(int)*3;
    IindexIfstream(const string &indexDir) {
        iindexTable.open(indexDir+"/"+"indextable", ios::binary);
        assert(iindexTable);
        iindexTerm.open(indexDir+"/"+"indexterm", ios::binary);
        assert(iindexTerm);
        iindexPostinglist.open(indexDir+"/"+"indexpostinglist", ios::binary);
        assert(iindexPostinglist);
    }
    int termNum() {
        return iindexTable.seekg(0,ios::end).tellg()/rowLength;
    }

    string getTerm(int termID) {
        int address;
        string term;
        iindexTable.seekg(rowLength*termID).read((char*)&address,sizeof(address));
        getline(iindexTerm.seekg(address),term,'\0');
        return term;
    }
    int getPostinglistBegin(int termID) {
        int address;
        iindexTable.seekg(rowLength*termID+sizeof(int)).read((char*)&address,sizeof(address));
        return address;

        //getline(iindexPostinglist.seekg(address),postingList,'\0');
        //return postingList;
    }
    int getDF(int termID) {
        int df;
        iindexTable.seekg(rowLength*termID+2*sizeof(int)).read((char*)&df,sizeof(df));
        return df;
    }
    string toString(int termID) {
        Posting p;
        string s;
        iindexPostinglist.seekg(getPostinglistBegin(termID));
        int df = getDF(termID);
        for (int i = 0; i<df; i++) {
            p.readFrom(iindexPostinglist);
            s += p.toString();
            s += " ";
        }
        return s;
    }
    string toString() {
        string s;
        for (int i = 0; i < termNum(); i++) {
            s += getTerm(i);
            s += ":";
            s += toString(i);
            s += "\n";
        }
        return s;
    }
};

#endif // IINDEXIFSTREAM_H_INCLUDED
