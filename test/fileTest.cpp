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
    IndexWriter iw(INDEX_DIR, make_shared<StandardAnalyzer>());
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
        cout << sd.doc << " : " << doc.getStoredField("title")->stringValue() <<endl;
    }

    is.close();
}

void fileTest(char*argv[]) {
    if(string(argv[1])=="-i") {
        if(string(argv[3])!="-d")
            throw invalid_argument("Command Error.");
        const string INDEX_DIR = argv[2];
        const string FILE_PATH = argv[4];
        fileTestIndex(INDEX_DIR,FILE_PATH);
    }else if(string(argv[1])=="-s") {
        const string INDEX_DIR = argv[2];
        if(string(argv[3])=="-b") {
            /*BooleanQuery
            string s = argv[4];
            QueryParser parser;
            shared_ptr<Query> query = parser.getQuery(s, make_shared<StandardAnalyzer>());
            */

            //test
            vector<shared_ptr<TermQuery>> v;
            v.push_back(make_shared<TermQuery>("the"));
            v.push_back(make_shared<TermQuery>("in"));
            v.push_back(make_shared<TermQuery>("language"));
            v.push_back(make_shared<TermQuery>("pronounce"));
            shared_ptr<Query> query=make_shared<PhraseQuery>(v,1);
            //test
            cout<<"Query: "<<query->toString()<<endl;
            fileTestSearchitem(INDEX_DIR, query);
        }
    }else {
        throw invalid_argument("Command Error.");
    }
    //fileTestIndex(INDEX_DIR,FILE_PATH);
    //TermQuery
    //shared_ptr<Query> query = make_shared<TermQuery>(item);
    //BooleanQuery
    // 0 1 2 3 4 5 6 8 9 10 11 12 13 14 15 16 17 18 19 21 22 23 24 26 28 29 32 33 35 36 37 39 40 43
/*
    shared_ptr<Query> q1 = make_shared<TermQuery>("gracious");
    // 2 12 21 26 28 33 43
    shared_ptr<Query> q2 = make_shared<TermQuery>("gracious,");
    // 19 27 38 40
    shared_ptr<Query> q3 = make_shared<TermQuery>("gracious.");
    // 15
    shared_ptr<Query> q4 = make_shared<TermQuery>("gracious:");
    // 7 12
    shared_ptr<Query> q5 = make_shared<TermQuery>("gracious;");
    // 14 23 33 37
    shared_ptr<Query> q6 = make_shared<TermQuery>("graciously");
    // 29
    shared_ptr<Query> q7 = make_shared<TermQuery>("graciously,");

    shared_ptr<BooleanQuery> query = make_shared<BooleanQuery>();
    query->add(BooleanQuery::MUST,q1);
    shared_ptr<BooleanQuery> subQuery = make_shared<BooleanQuery>();
    subQuery->add(BooleanQuery::SHOULD, q2);
    subQuery->add(BooleanQuery::SHOULD, q3);
    query->add(BooleanQuery::MUST_NOT,subQuery);
*/

}
