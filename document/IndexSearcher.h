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
class IndexSearcher {
public:
    string indexDir;
    StoredIfstream storedIfstream;
    IndexSearcher(const string &indexDir):storedIfstream(indexDir){
        this->indexDir = indexDir;
    }
    vector<ScoreDoc> search(shared_ptr<Query> query){return{};}
    Document doc(int docID){
        return {};
    }
    void close(){
        IindexIfstream iindexIfstream(indexDir);
        //cout << iindexIfstream.termNum();
        //cout << iindexIfstream.toString();
        cout << storedIfstream.toString(1);
    }
};

#endif // INDEXSEARCHER_H_INCLUDED
