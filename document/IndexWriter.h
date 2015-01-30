#ifndef INDEXWRITER_H_INCLUDED
#define INDEXWRITER_H_INCLUDED

#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
using namespace std;
#include "../analyzer/Analyzer.h"
#include "Posting.h"
#include "InvertedIndex.h"

class IndexWriter {
public:
    ofstream sfieldTable,sfieldText;
    string indexDir;
    shared_ptr<Analyzer> analyzer;
    vector<string> fieldNameList;
    size_t nextDocID;
    InvertedIndex iindex;
    IndexWriter(const string &indexDir, shared_ptr<Analyzer> analyzer){
        this->indexDir = indexDir;
        this->analyzer = analyzer;
        nextDocID = 0;
    }
    void setStoredField(const vector<string> &fieldname){
    }
    void addDocument(const Document &doc) {
        iindex.addDocTokens(nextDocID, analyzer->toTokens(doc.textField->text));
        nextDocID++;
    }
    void close(){
        cout << iindex.toString();
    }
};

//IndexWiter:

#endif // INDEXWRITER_H_INCLUDED
