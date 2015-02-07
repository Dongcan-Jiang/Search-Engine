#include "test.h"

void simpleTestIndex(const string & INDEX_DIR, const vector<vector<string>> &dataset) {
    IndexWriter iw(INDEX_DIR, make_shared<WhitespaceAnalyzer>());
    iw.setStoredField(vector<string>{"title", "t1" ,"t2"});
    for (auto &data : dataset) {
        Document doc;
        shared_ptr<TextField> textField = make_shared<TextField>(data[1]);
        shared_ptr<StoredField> titleField = make_shared<StoredField>("title", data[0]);
        shared_ptr<StoredField> t1Field = make_shared<StoredField>("t1", data[2]);
        shared_ptr<StoredField> t2Field = make_shared<StoredField>("t2", data[3]);
        doc.setTextField(textField);
        doc.addStoredField(titleField);
        doc.addStoredField(t1Field);
        doc.addStoredField(t2Field);
        iw.addDocument(doc);
    }
    iw.close();
}

void simpleTestSearchitem(const string & INDEX_DIR, const string &item) {
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
    const string INDEX_DIR = "index/";
    vector<vector<string>> dataset = {
        {"doc1", "a b a", "afadljfadjlkdfajfl", "fadfdfjlaf"},
        {"doc2", "x a e", "fadjfklqjfoqejf;qmqc", "fasffeqfrghtht"},
        {"doc3", "l x y t","fadfqefqef", "omfqfoqefjio"},
        {"doc4", "k b r d w", "fafqefhwtherg", "fafqgeg"},
        {"doc5", "u t w x a", "a", "b"},
        {"doc6", "m t a","gqo","mpijpih"}
    };
    //simpleTestIndex(INDEX_DIR, dataset);
    simpleTestSearchitem(INDEX_DIR, "b");
}
