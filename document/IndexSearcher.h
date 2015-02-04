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
    IindexIfstream iindexIfstream;
    IndexSearcher(const string &indexDir):storedIfstream(indexDir),iindexIfstream(indexDir){
        this->indexDir = indexDir;
    }
    vector<ScoreDoc> search(shared_ptr<Query> query){return{};}
    Document doc(int docID){
        return storedIfstream.doc(docID);
    }
    void close(){
        storedIfstream.close();
        iindexIfstream.close();
    }
};

#endif // INDEXSEARCHER_H_INCLUDED
