#ifndef INDEXSEARCHER_H_INCLUDED
#define INDEXSEARCHER_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;
#include "ScoreDoc.h"
#include "../query/Query.h"
#include "IindexIfstream.h"
#include "StoredIfstream.h"
#include "../scorer/Scorer.h"

class IndexSearcher {
public:
    string indexDir;
    StoredIfstream storedIfstream;
    IindexIfstream iindexIfstream;

    IndexSearcher(const string &indexDir):storedIfstream(indexDir),iindexIfstream(indexDir){
        this->indexDir = indexDir;
    }

    vector<ScoreDoc> search(shared_ptr<Query> query){
        shared_ptr<Scorer> sc = query->getScorer(*this);
        vector<ScoreDoc> sds;
        while(sc->next() < Scorer::DOC_EXHAUSTED) {
            ScoreDoc sd(sc->doc());
            sds.push_back(sd);
        }
        return sds;
    }

    Document doc(int docID){
        return storedIfstream.doc(docID);
    }

    void close(){
        storedIfstream.close();
        iindexIfstream.close();
    }

};

#endif // INDEXSEARCHER_H_INCLUDED
