#include "test.h"

void simpleTestIndex(const string & INDEX_DIR, const vector<vector<string>> &dataset) {
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

void simpleTestSearchitem(const string & INDEX_DIR, const vector<vector<string>> &dataset, const string &item) {
    IndexSearcher is(INDEX_DIR);
    shared_ptr<Query> query = make_shared<TermQuery>(item);
    vector<ScoreDoc> docs = is.search(query);
    for (auto &sd : docs) {
        Document doc = is.doc(sd.doc);
        cout << doc.getStoredField("title")->stringValue() <<endl;
    }
    is.close();
}

void simpleTest() {
    const string INDEX_DIR = "index";
    vector<vector<string>> dataset = {
        {"doc1", "a b c d e f g a"},
        {"doc2", "x a e c d"},
        {"doc3", "l x y t"},
        {"doc4", "k b r d w"},
        {"doc5", "u t w x a"},
        {"doc6", "m t a"}
    };
    simpleTestIndex(INDEX_DIR, dataset);
    //simpleTestSearchitem(INDEX_DIR, dataset, "a");
}
