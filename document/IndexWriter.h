#ifndef INDEXWRITER_H_INCLUDED
#define INDEXWRITER_H_INCLUDED

#include <fstream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
using namespace std;
#include "../analyzer/Analyzer.h"
#include "Posting.h"
class IndexWriter {
public:
    ofstream sfieldTable,sfieldText;
    map<string, vector<Posting>> invertedindex;
    vector<string> fieldNameList;
    IndexWriter(string index_dir, shared_ptr<Analyzer> analyzer){}
    void setStoredField(const vector<string> &fieldname){}
    void addDocument(Document doc) {}
    void close(){}
};

//IndexWiter:

#endif // INDEXWRITER_H_INCLUDED
