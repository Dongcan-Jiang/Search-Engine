#include <string>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

#include "analyzer/Token.h"
#include "analyzer/Analyzer.h"
#include "analyzer/WhitespaceAnalyzer.h"
#include "document/Document.h"
#include "document/IndexSearcher.h"
#include "document/IndexWriter.h"
#include "document/Posting.h"
#include "document/ScoreDoc.h"
#include "document/StoredField.h"
#include "document/TextField.h"
#include "query/Query.h"
#include "query/TermQuery.h"


void index(const string & INDEX_DIR, const vector<vector<string>> &dataset) {
    IndexWriter iw(INDEX_DIR, make_shared<WhitespaceAnalyzer>());
    iw.setStoredField(vector<string>{"title"});
    for (auto &data : dataset) {
        Document doc;
        shared_ptr<TextField> textField = make_shared<TextField>(data[1]);
        shared_ptr<StoredField> titleField = make_shared<StoredField>("title", data[0]);
        doc.setTextField(textField);
        doc.addStoredField(titleField);
        iw.addDocument(doc);
    }
    iw.close();
}

void searchitem(const string & INDEX_DIR, const vector<vector<string>> &dataset, const string &item) {
    IndexSearcher is(INDEX_DIR);
    shared_ptr<Query> query = make_shared<TermQuery>(item);
    vector<ScoreDoc> docs = is.search(query);
    for (auto &sd : docs) {
        Document doc = is.doc(sd.doc);
        cout << doc.getStoredField("title")->stringValue() <<endl;
    }
    is.close();
}

int main() {
    const string INDEX_DIR = "index";
    vector<vector<string>> dataset = {
        {"doc1", "a b c d e f g"},
        {"doc2", "x a e c d"},
        {"doc3", "l x y t"},
        {"doc4", "k b r d w"},
        {"doc5", "u t w x a"},
        {"doc6", "m t a"}
    };
    index(INDEX_DIR, dataset);
    searchitem(INDEX_DIR, dataset, "a");
    return 0;
}
