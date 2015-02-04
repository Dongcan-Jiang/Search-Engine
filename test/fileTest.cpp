#include "test.h"


void readFromFile(IndexWriter &iw, const string &filename) {
    ifstream fin(filename,ios::binary);
    int length = fin.seekg(0,ios::end).tellg();
    char s[length+1];
    fin.seekg(0,ios::beg);
    fin.read(s,length);
    s[length] = '\0';
    Document doc;
    string text(s);
    shared_ptr<TextField> textField = make_shared<TextField>(text);
    int t = filename.rfind('/')+1;
    shared_ptr<StoredField> titleField = make_shared<StoredField>("title", filename.substr(t,filename.size()-t));
    shared_ptr<StoredField> pathField = make_shared<StoredField>("path", filename);
    /*
    int f = text.find(' ');
    shared_ptr<StoredField> firstWordField = make_shared<StoredField>("firstword",text.substr(0,f));
    */
    doc.setTextField(textField);
    doc.addStoredField(titleField);
    doc.addStoredField(pathField);
    //doc.addStoredField(firstWordField);
    iw.addDocument(doc);
    fin.close();
}


void fileTestIndex(const string & INDEX_DIR, const string & FILE_PATH) {
    IndexWriter iw(INDEX_DIR, make_shared<WhitespaceAnalyzer>());
    iw.setStoredField(vector<string>{"title", "path"});

    fs::traverse(FILE_PATH, [&iw](const string & filename){
        readFromFile(iw, filename);
    });

    iw.close();
}

void fileTestSearchitem(const string & INDEX_DIR, const string &item) {
    IndexSearcher is(INDEX_DIR);

    /*
    shared_ptr<Query> query = make_shared<TermQuery>(item);
    vector<ScoreDoc> docs = is.search(query);
    for (auto &sd : docs) {
        Document doc = is.doc(sd.doc);
        cout << doc.getStoredField("title")->stringValue() <<endl;
    }
    */

    //just for test. the parameter is meaningless
    is.doc(1);

    is.close();
}

void fileTest() {
    const string INDEX_DIR = "index/";
    const string FILE_PATH = "shakespeare/input";
    //fileTestIndex(INDEX_DIR,FILE_PATH);
    fileTestSearchitem(INDEX_DIR, "a");
}
