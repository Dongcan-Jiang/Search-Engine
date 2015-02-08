#include "test.h"

string readText(const string &path) {
    ifstream fin(path, ios::binary);
    int length = fin.seekg(0,ios::end).tellg();
    char s[length+1];
    fin.seekg(0,ios::beg);
    fin.read(s,length);
    s[length] = '\0';
    string text(s);
    fin.close();
    return text;
}

void readFromFile(IndexWriter &iw, const string &path) {
    Document doc;
    string text = readText(path);
    shared_ptr<TextField> textField = make_shared<TextField>(text);
    int t = path.rfind('/')+1;
    shared_ptr<StoredField> titleField = make_shared<StoredField>("title", path.substr(t,path.size()-t));
    shared_ptr<StoredField> pathField = make_shared<StoredField>("path", path);
    /*
    int f = text.find(' ');
    shared_ptr<StoredField> firstWordField = make_shared<StoredField>("firstword",text.substr(0,f));
    */
    doc.setTextField(textField);
    doc.addStoredField(titleField);
    doc.addStoredField(pathField);
    //doc.addStoredField(firstWordField);
    iw.addDocument(doc);
}

void fileTestIndex(const string & INDEX_DIR, const string & FILE_PATH) {
    IndexWriter iw(INDEX_DIR, make_shared<WhitespaceAnalyzer>());
    iw.setStoredField(vector<string>{"title", "path"});

    fs::traverse(FILE_PATH, [&iw](const string & path){
        readFromFile(iw, path);
    });

    iw.close();
}

void fileTestSearchitem(const string & INDEX_DIR, shared_ptr<Query> query) {
    IndexSearcher is(INDEX_DIR);
    vector<ScoreDoc> docs = is.search(query);

    for (auto &sd : docs) {
        Document doc = is.doc(sd.doc);
        cout << doc.getStoredField("title")->stringValue() <<endl;
    }

    is.close();
}

void fileTest() {
    const string INDEX_DIR = "index/";
    const string FILE_PATH = "shakespeare/input";
    //fileTestIndex(INDEX_DIR,FILE_PATH);
    //TermQuery
    //shared_ptr<Query> query = make_shared<TermQuery>(item);

    //BooleanQuery
    shared_ptr<Query> q1 = make_shared<TermQuery>("gracious,");
    shared_ptr<Query> q2 = make_shared<TermQuery>("gracious");
    shared_ptr<Query> q3 = make_shared<TermQuery>("gracious;");
    shared_ptr<Query> q4 = make_shared<TermQuery>("gratis.");
    shared_ptr<BooleanQuery> query = make_shared<BooleanQuery>();
    query->add(BooleanQuery::MUST,q1);
    query->add(BooleanQuery::MUST,q2);
    query->add(BooleanQuery::MUST_NOT,q3);
    query->add(BooleanQuery::MUST_NOT,q4);
    fileTestSearchitem(INDEX_DIR, query);
}
