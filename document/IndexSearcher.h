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
class IndexSearcher {
public:
    ifstream sfieldTable,sfieldText,sfieldNamelist;
    IindexIfstream iindexIfstream;
    IndexSearcher(const string &INDEX_DIR){}
    vector<ScoreDoc> search(shared_ptr<Query> query){}
    Document doc(int docID){}
    void close(){}
};

#endif // INDEXSEARCHER_H_INCLUDED