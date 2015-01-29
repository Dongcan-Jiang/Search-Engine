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

class IndexSearcher {
public:
    ifstream iindexTable,iindexTerm,iindexPostinglist,sfieldTable,sfieldText,sfieldNamelist;
    IndexSearcher(const string &INDEX_DIR){}
    vector<ScoreDoc> search(shared_ptr<Query> query){}
    Document doc(int docID){}
    void close(){}
};

#endif // INDEXSEARCHER_H_INCLUDED
