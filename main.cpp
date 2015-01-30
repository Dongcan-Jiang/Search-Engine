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
    WhitespaceAnalyzer test;
    vector<Token> tokens;
    tokens = test.toTokens("a b c");
    for (size_t i = 0; i< tokens.size(); i++)
        cout << tokens[i].toString()<< "+";

}
