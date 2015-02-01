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
    ofstream sfTable,sfText;
    string indexDir;
    shared_ptr<Analyzer> analyzer;
    vector<string> fieldNameList;
    int nextDocID;
    InvertedIndex iindex;
    IndexWriter(const string &indexDir, shared_ptr<Analyzer> analyzer){
        this->indexDir = indexDir;
        this->analyzer = analyzer;
        nextDocID = 0;
        sfTable.open(indexDir+"storedfieldtable", ios::binary);
        sfText.open(indexDir+"storedfieldtext", ios::binary);
    }
    void setStoredField(const vector<string> &fieldname){
        this->fieldNameList = fieldname;
    }
    void addDocument(const Document &doc) {
        iindex.addDocTokens(nextDocID, analyzer->toTokens(doc.textField->text));
        string s;
        int t = sfText.tellp();
        sfTable.write((char*)&t, sizeof(int));
        for(auto & name : fieldNameList) {
            s = doc.storedField.find(name)->second->stored;
            sfText.write(s.c_str(),s.size()+1);
        }
        nextDocID++;
    }
    void close(){
        //cout << iindex.toString();
        sfTable.close();
        sfText.close();
        iindex.save(indexDir);
    }
};

//IndexWiter:

#endif // INDEXWRITER_H_INCLUDED
